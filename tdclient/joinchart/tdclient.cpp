#include <QCoreApplication>

#include "tdclient.h"
#include <QTimer>
#include "logout.h"


TdClient::TdClient()
{
	td::Log::set_verbosity_level(1);
	client_ = std::make_unique<td::Client>();
	send_query(td_api::make_object<td::td_api::addProxy>(td::td_api::addProxy(
		"172.105.196.90", 1984, true,
		td::td_api::object_ptr<td::td_api::ProxyType>(
			new td::td_api::proxyTypeMtproto("c4127cc0eb363cb4b7b35e6deb5674e8")))),
			{});
	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, &QTimer::timeout, this, [&]() {
		update();
	});

	timer_send = new QTimer(this);
	timer_send->setInterval(20000);
	connect(timer_send, &QTimer::timeout, this, [&]() {
		;// update_send();
	});
	qRegisterMetaType<Chat>();

	LogOut::GetInstance()->setMaxLine(1250);
	LogOut::GetInstance()->setFileName(QCoreApplication::applicationDirPath() + "/msg");
	getmap();
}

void TdClient::loop()
{

	//
	while (true) {
		if (need_restart_) {
			restart();
		}
		else if (!are_authorized_) {
			process_response(client_->receive(10));
		}
		else {
			break;
		}
	}
}

void TdClient::logout()
{
	std::cerr << "Logging out..." << std::endl;
	send_query(td_api::make_object<td_api::logOut>(), {});
}

void TdClient::sendMessage(std::int64_t chat_id, std::string text)
{
	std::cerr << "Sending message to chat " << chat_id << "..." << std::endl;
	auto send_message = td_api::make_object<td_api::sendMessage>();
	send_message->chat_id_ = chat_id;
	auto message_content = td_api::make_object<td_api::inputMessageText>();
	message_content->text_ = td_api::make_object<td_api::formattedText>();
	message_content->text_->text_ = std::move(text);
	send_message->input_message_content_ = std::move(message_content);

	send_query(std::move(send_message), {});
}

void TdClient::loadChatList()
{
	std::cerr << "Loading chat list..." << std::endl;
	timer->start();
	timer_send->start();

	send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
		[this](Object object) {
		if (object->get_id() == td_api::error::ID) {
			return;
		}
		auto chats = td::move_tl_object_as<td_api::chats>(object);
		QList<Chat> chatList;
		for (auto chat_id : chats->chat_ids_) {
			Chat chat;
			chat.id = chat_id;
			chat.title = chat_title_[chat_id].c_str();
			chatList << chat;
			std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;

			QString chartid = QString::number(chat_id);
			QString chart_text = QString::number(chat_id) + "] [from:" + chat_title_[chat_id].c_str() + "]";
			LogOut::GetInstance()->setMaxLine(2970);
			LogOut::GetInstance()->setFileName(QCoreApplication::applicationDirPath() + "/msgchart");
			LogOut::GetInstance()->printLog(chart_text);
			
		}
		emit chatListResult(chatList);
	});
}

void TdClient::update()
{

	//std::cout << "update..." << std::endl;
	auto response = client_->receive(0);
	if (response.object) {
		process_response(std::move(response));
	}
}



void TdClient::authorize()
{
	process_response(client_->receive(10));
}

void TdClient::getUserInput()
{
	std::cerr << "Enter action [q] quit [u] check for updates and request results [c] show chats [m <id> <text>] "
		"send message [j <group invite link>] join group [g <id>] leave group [l] logout: "
		<< std::endl;
	std::string line;
	std::getline(std::cin, line);
	std::istringstream ss(line);
	std::string action;
	ss >> action;
	if (action == "q") {
		return;
	}
	if (action == "u") {
		std::cerr << "Checking for updates..." << std::endl;
		while (true) {
			auto response = client_->receive(0);
			if (response.object) {
				process_response(std::move(response));
			}
			else {
				break;
			}
		}
	}
	else if (action == "l") {
		std::cerr << "Logging out..." << std::endl;
		send_query(td_api::make_object<td_api::logOut>(), {});
	}
	else if (action == "m") {
		std::int64_t chat_id;
		ss >> chat_id;
		ss.get();
		std::string text;
		std::getline(ss, text);

		std::cerr << "Sending message to chat " << chat_id << "..." << std::endl;
		auto send_message = td_api::make_object<td_api::sendMessage>();
		send_message->chat_id_ = chat_id;
		auto message_content = td_api::make_object<td_api::inputMessageText>();
		message_content->text_ = td_api::make_object<td_api::formattedText>();
		message_content->text_->text_ = std::move(text);
		send_message->input_message_content_ = std::move(message_content);

		send_query(std::move(send_message), {});
	}
	else if (action == "c") {
		std::cerr << "Loading chat list..." << std::endl;
		send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
			[this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				return;
			}
			auto chats = td::move_tl_object_as<td_api::chats>(object);
			for (auto chat_id : chats->chat_ids_) {
				std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
			}
		});
	}
	else if (action == "j") {
	/*	update_send();
		return;*/
		std::cerr << "Join group..." << std::endl;
		std::string joinLink;
		std::getline(ss, joinLink);
		send_query(td_api::make_object<td_api::joinChatByInviteLink>(joinLink), [this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				return;
			}
			std::cerr << "join group succ.";
			send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
				[this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					return;
				}
				auto chats = td::move_tl_object_as<td_api::chats>(object);
				for (auto chat_id : chats->chat_ids_) {
					std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
				}
			});
		});
	}
	else if (action == "g") {
		std::cerr << "Leave group..." << std::endl;
		std::int64_t chat_id;
		ss >> chat_id;
		ss.get();
		std::cerr << chat_id;
		send_query(td_api::make_object<td_api::leaveChat>(chat_id), [this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				std::cerr << "Leave group error.";													                return;
			}
			std::cerr << "Leave group succ.";
			send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
				[this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					return;
				}
				auto chats = td::move_tl_object_as<td_api::chats>(object);
				for (auto chat_id : chats->chat_ids_) {
					std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
				}
			});
		});
	}
	/*QTimer::singleShot(1000,this,[&](){
	*         getUserInput();
	*             });*/
}

void TdClient::execCommand(QString cmd)
{

	std::string line = cmd.toUtf8().data();
	std::istringstream ss(line);
	std::string action;
	ss >> action;
	if (action == "q") {
		return;
	}
	if (action == "u") {
		std::cerr << "Checking for updates..." << std::endl;
		while (true) {
			auto response = client_->receive(0);
			if (response.object) {
				process_response(std::move(response));
			}
			else {
				break;
			}
		}
	}
	else if (action == "l") {
		std::cerr << "Logging out..." << std::endl;
		send_query(td_api::make_object<td_api::logOut>(), {});
	}
	else if (action == "m") {
		std::int64_t chat_id;
		ss >> chat_id;
		ss.get();
		std::string text;
		std::getline(ss, text);

		std::cerr << "Sending message to chat " << chat_id << "..." << std::endl;
		auto send_message = td_api::make_object<td_api::sendMessage>();
		send_message->chat_id_ = chat_id;
		auto message_content = td_api::make_object<td_api::inputMessageText>();
		message_content->text_ = td_api::make_object<td_api::formattedText>();
		message_content->text_->text_ = std::move(text);
		send_message->input_message_content_ = std::move(message_content);

		send_query(std::move(send_message), {});
	}
	else if (action == "c") {
		std::cerr << "Loading chat list..." << std::endl;
		send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
			[this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				return;
			}
			auto chats = td::move_tl_object_as<td_api::chats>(object);
			for (auto chat_id : chats->chat_ids_) {
				
				std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
			}
		});
	}
	else if (action == "j") {
		update_send();
		return;
		std::cerr << "Join group..." << std::endl;
		std::string joinLink;
		ss >> joinLink;
		if (joinLink.find("joinchat") == std::string::npos) {
			send_query(td_api::make_object<td_api::searchPublicChat>(joinLink), [this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					auto error = td::move_tl_object_as<td_api::error>(object);
					std::cerr << error->message_;
					return;
				}
				auto chat = td::move_tl_object_as<td_api::chat>(object);
				std::cerr << "[id:" << chat->id_ << "] [title:" << chat->title_ << "]" << std::endl;
				send_query(td_api::make_object<td_api::joinChat>(chat->id_), [this](Object object) {
					if (object->get_id() == td_api::error::ID) {
						auto error = td::move_tl_object_as<td_api::error>(object);
						std::cerr << error->message_;
						return;
					}
					std::cerr << "join success.";
					send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20), [this](Object object) {																											if (object->get_id() == td_api::error::ID) {
						return;
					}
					auto chats = td::move_tl_object_as<td_api::chats>(object);
					for (auto chat_id : chats->chat_ids_) {
						std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
					}
					});
				});

			});
		}
		else {
			std::cerr << "Join group..joinChatByInviteLink." << std::endl;

			send_query(td_api::make_object<td_api::joinChatByInviteLink>(joinLink), [this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					auto error = td::move_tl_object_as<td_api::error>(object);
					std::cerr << error->message_;
					return;
				}
				std::cerr << "join success.";
				send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20), [this](Object object) {
					if (object->get_id() == td_api::error::ID) {
						return;
					}
					auto chats = td::move_tl_object_as<td_api::chats>(object);
					for (auto chat_id : chats->chat_ids_) {
						std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
					}
				});
			});
		}
	}
	else if (action == "g") {
		std::cerr << "Leave group..." << std::endl;
		std::int64_t chat_id;
		ss >> chat_id;
		ss.get();
		send_query(td_api::make_object<td_api::leaveChat>(chat_id), [this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				return;
			}
			send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20), [this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					return;
				}
				auto chats = td::move_tl_object_as<td_api::chats>(object);
				for (auto chat_id : chats->chat_ids_) {
					std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
				}
			});
		});
	}
}

void TdClient::restart()
{
	client_.reset();
	//*this = TdClient();
}

void TdClient::send_query(td_api::object_ptr<td_api::Function> f, std::function<void(Object)> handler)
{
	auto query_id = next_query_id();
	if (handler) {
		handlers_.emplace(query_id, std::move(handler));
	}
	client_->send({ query_id, std::move(f) });
}

void TdClient::process_response(td::Client::Response response)
{
	if (!response.object) {
		return;
	}
	//std::cerr << response.id << " " << to_string(response.object) << std::endl;
	if (response.id == 0) {
		return process_update(std::move(response.object));
	}
	auto it = handlers_.find(response.id);
	if (it != handlers_.end()) {
		it->second(std::move(response.object));
	}
}

std::string TdClient::get_user_name(std::int32_t user_id)
{
	auto it = users_.find(user_id);
	if (it == users_.end()) {
		return "unknown user";
	}
	return it->second->first_name_ + " " + it->second->last_name_;
}

void TdClient::process_update(td_api::object_ptr<td_api::Object> update)
{
	td_api::downcast_call(
		*update, overloaded(
			[this](td_api::updateAuthorizationState &update_authorization_state) {
		authorization_state_ = std::move(update_authorization_state.authorization_state_);
		on_authorization_state_update();
	},
			[this](td_api::updateNewChat &update_new_chat) {
		chat_title_[update_new_chat.chat_->id_] = update_new_chat.chat_->title_;
	},
		[this](td_api::updateChatTitle &update_chat_title) {
		chat_title_[update_chat_title.chat_id_] = update_chat_title.title_;
	},
		[this](td_api::updateUser &update_user) {
		auto user_id = update_user.user_->id_;
		users_[user_id] = std::move(update_user.user_);
	},
		[this](td_api::updateNewMessage &update_new_message) {
		auto chat_id = update_new_message.message_->chat_id_;
		auto sender_user_name = get_user_name(update_new_message.message_->sender_user_id_);
		std::string text;
		if (update_new_message.message_->content_->get_id() == td_api::messageText::ID) {
			text = static_cast<td_api::messageText &>(*update_new_message.message_->content_).text_->text_;
		}
		if (update_new_message.message_->content_->get_id() == td_api::messageChatDeleteMember::ID)
		{
			text = QString("%1 leave group").arg(get_user_name(static_cast<td_api::messageChatDeleteMember &>(*update_new_message.message_->content_).user_id_).c_str()).toUtf8().data();
		}
		if (update_new_message.message_->content_->get_id() == td_api::messageChatAddMembers::ID)
		{
			auto ids = static_cast<td_api::messageChatAddMembers &>(*update_new_message.message_->content_).member_user_ids_;
			foreach(auto id, ids)
			{
				text += QString("%1,").arg(get_user_name(id).c_str()).toUtf8().data();
			}
			text += "add group";
		}
		std::cerr << "Got message: [chat_id:" << chat_id << "] [from:" << sender_user_name << "] ["
			<< text << "]" << std::endl;

		QString chartid = QString::number(chat_id);
		QString chart_text = QString::number(chat_id) + "] [from:" + sender_user_name.c_str() + "] [" + text.c_str() + "]";

		//if (chartid.indexOf("-") != -1 && text.find("add group") == -1)
		{
			LogOut::GetInstance()->setMaxLine(970);
			LogOut::GetInstance()->setFileName(QCoreApplication::applicationDirPath() + "/msg/" + chartid);
			LogOut::GetInstance()->printLog(chart_text);
		}

		emit newMessage(chat_id, sender_user_name.c_str(), text.c_str());
	},
		[](auto &update) {}));
}

auto TdClient::create_authentication_query_handler()
{
	return [this, id = authentication_query_id_](Object object) {
		if (id == authentication_query_id_) {
			check_authentication_error(std::move(object));
		}
	};
}

void TdClient::on_authorization_state_update()
{
	authentication_query_id_++;
	td_api::downcast_call(
		*authorization_state_,
		overloaded(
			[this](td_api::authorizationStateReady &) {
		are_authorized_ = true;
		emit authSuccess();
		std::cerr << "Got authorization" << std::endl;
	},
			[this](td_api::authorizationStateLoggingOut &) {
		are_authorized_ = false;
		std::cerr << "Logging out" << std::endl;
	},
		[this](td_api::authorizationStateClosing &) { std::cerr << "Closing" << std::endl; },
		[this](td_api::authorizationStateClosed &) {
		are_authorized_ = false;
		need_restart_ = true;
		std::cerr << "Terminated" << std::endl;
	},
		[this](td_api::authorizationStateWaitCode &wait_code) {
		std::string first_name;
		std::string last_name;
		if (!wait_code.is_registered_) {
			std::cerr << "Enter your first name: ";
			std::cin >> first_name;
			std::cerr << "Enter your last name: ";
			std::cin >> last_name;
		}
		std::cerr << "Enter authentication code: ";
		std::string code;
		std::cin >> code;
		send_query(td_api::make_object<td_api::checkAuthenticationCode>(code, first_name, last_name),
			create_authentication_query_handler());
	},
		[this](td_api::authorizationStateWaitPassword &) {
		std::cerr << "Enter authentication password: ";
		std::string password;
		std::cin >> password;
		send_query(td_api::make_object<td_api::checkAuthenticationPassword>(password),
			create_authentication_query_handler());
	},
		[this](td_api::authorizationStateWaitPhoneNumber &) {
		std::cerr << "Enter phone number: ";
		std::string phone_number;
		std::cin >> phone_number;
		send_query(td_api::make_object<td_api::setAuthenticationPhoneNumber>(
			phone_number, false /*allow_flash_calls*/, false /*is_current_phone_number*/),
			create_authentication_query_handler());
	},
		[this](td_api::authorizationStateWaitEncryptionKey &) {
		send_query(td_api::make_object<td_api::checkDatabaseEncryptionKey>(std::move("123123")),
			create_authentication_query_handler());
	},
		[this](td_api::authorizationStateWaitTdlibParameters &) {
		auto parameters = td_api::make_object<td_api::tdlibParameters>();

		QString dir = QString(qApp->applicationDirPath() + "/tdlib");
		parameters->database_directory_ = dir.toStdString();
		parameters->use_message_database_ = true;
		parameters->use_secret_chats_ = true;
		parameters->api_id_ = 684182;
		parameters->api_hash_ = "2f7d65c9267422faa3addafd259b50a1";
		parameters->system_language_code_ = "en";
		parameters->device_model_ = "Desktop";
		parameters->system_version_ = "Unknown";
		parameters->application_version_ = "1.0";
		parameters->enable_storage_optimizer_ = true;
		send_query(td_api::make_object<td_api::setTdlibParameters>(std::move(parameters)),
			create_authentication_query_handler());
	}));
}


void TdClient::check_authentication_error(Object object)
{
	if (object->get_id() == td_api::error::ID) {
		auto error = td::move_tl_object_as<td_api::error>(object);
		std::cerr << "Error: " << to_string(error);
		on_authorization_state_update();
	}
}

std::uint64_t TdClient::next_query_id()
{
	return ++current_query_id_;
}

#include <QDir> 
#include <QTime> 
void TdClient::update_send()
{
	QFile fileObj(QCoreApplication::applicationDirPath() + "/chart");
	fileObj.open(QIODevice::ReadOnly);
	QTextStream in(&fileObj);

	int ji = 0;
	while (!in.atEnd())
	{
		QString temptext = in.readLine();
		if (temptext.isEmpty())
			continue;

		std::string joinLink = temptext.toStdString();
		joinchart(temptext);

		{
			QEventLoop loop;
			QTimer::singleShot(20000, &loop, SLOT(quit()));
			loop.exec();
		}

	}
	fileObj.close();
}

void TdClient::joinchart(const QString temptext)
{
	std::string joinLink = temptext.toStdString();	
	joinLink.erase(joinLink.find_last_not_of('\r') + 1);
	joinLink.erase(joinLink.find_last_not_of('\n') + 1);


	std::cerr << "Join group...[" << joinLink <<"]"<< std::endl;

	if (joinLink.find("joinchat") == std::string::npos)
	{
		send_query(td_api::make_object<td_api::searchPublicChat>(joinLink), [this](Object object)
		{
			if (object->get_id() == td_api::error::ID) {
				auto error = td::move_tl_object_as<td_api::error>(object);
				std::cerr << error->message_;
				return;
			}
			auto chat = td::move_tl_object_as<td_api::chat>(object);
			std::cerr << "[id:" << chat->id_ << "] [title:" << chat->title_ << "]" << std::endl;
			send_query(td_api::make_object<td_api::joinChat>(chat->id_), [this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					auto error = td::move_tl_object_as<td_api::error>(object);
					std::cerr << error->message_;
					return;
				}
				std::cerr << "join success.";
				send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20), [this](Object object) {																											if (object->get_id() == td_api::error::ID) {
					return;
				}
				auto chats = td::move_tl_object_as<td_api::chats>(object);
				for (auto chat_id : chats->chat_ids_) {
					std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
					////////////////

					////////////////

				}
				});
			});

		});
	}
	else
	{
		std::string joinLinkt = "t.me/" + joinLink;


		send_query(td_api::make_object<td_api::joinChatByInviteLink>(joinLinkt), [this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				return;
			}
			std::cerr << "join group succ.";
			send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
				[this](Object object) {
				if (object->get_id() == td_api::error::ID) {
					return;
				}
				auto chats = td::move_tl_object_as<td_api::chats>(object);
				for (auto chat_id : chats->chat_ids_) {
					std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
				}
			});
		});
	}
}


QString TdClient::getchartname(QString chartid)
{	
	int p = m_chartidName.indexOf(chartid);
	int p12 = m_chartidName.indexOf("|", p);
	QString res = m_chartidName.mid(p12+14);
	int pt = res.indexOf("-");
	if(pt != -1)
		res = res.mid(0,pt);
	res = res.simplified();	
	return res;
}


void TdClient::getmap()
{
	QFile fileObj(QCoreApplication::applicationDirPath() + "/maptxt");
	fileObj.open(QIODevice::ReadOnly);
	QByteArray fileDataTemp = fileObj.readAll();
	QString fileData(fileDataTemp);
	m_chartidName = fileData;	
}



void TdClient::Leavegroup(QString cstr)
{
	std::int64_t chat_id = cstr.toLong();
	std::cerr << "Leave group..." << std::endl;

	send_query(td_api::make_object<td_api::leaveChat>(chat_id), [this](Object object) {
		if (object->get_id() == td_api::error::ID) {
			std::cerr << "Leave group error.";													                return;
		}
		std::cerr << "Leave group succ.";
		send_query(td_api::make_object<td_api::getChats>(std::numeric_limits<std::int64_t>::max(), 0, 20),
			[this](Object object) {
			if (object->get_id() == td_api::error::ID) {
				return;
			}
			auto chats = td::move_tl_object_as<td_api::chats>(object);
			for (auto chat_id : chats->chat_ids_) {
				std::cerr << "[id:" << chat_id << "] [title:" << chat_title_[chat_id] << "]" << std::endl;
			}
		});
	});
}
