#pragma once

#include <QObject>
#include <QDebug>
#include <QString>
#include <td/telegram/Client.h>
#include <td/telegram/Log.h>
#include <td/telegram/td_api.h>
#include <td/telegram/td_api.hpp>

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "utility.h"
// overloaded
namespace detail {
	template <class... Fs>
	struct overload;

	template <class F>
	struct overload<F> : public F {
		explicit overload(F f) : F(f) {
		}
	};
	template <class F, class... Fs>
	struct overload<F, Fs...>
		: public overload<F>
		, overload<Fs...> {
		overload(F f, Fs... fs) : overload<F>(f), overload<Fs...>(fs...) {
		}
		using overload<F>::operator();
		using overload<Fs...>::operator();
	};
}  // namespace detail

template <class... F>
auto overloaded(F... f) {
	return detail::overload<F...>(f...);
}

namespace td_api = td::td_api;
class QTimer;
class TdClient :public QObject {
	Q_OBJECT
public:
	TdClient();
	std::string dbPassword, phoneNumber, firstName, lastName;
public slots:
	void loop();
	void logout();
	void sendMessage(std::int64_t chat_id, std::string text);
	void loadChatList();
	void update();
	void authorize();
    void getUserInput();
	void execCommand(QString cmd);

signals:
	void chatListResult(QList<Chat> chats);
	void newMessage(qint64 chatId,QString senderName,QString content);
	void authSuccess();
private:
	using Object = td_api::object_ptr<td_api::Object>;
	std::unique_ptr<td::Client> client_;
	QTimer *timer;
	QTimer *timer_send;
	td_api::object_ptr<td_api::AuthorizationState> authorization_state_;
	bool are_authorized_{ false };
	bool need_restart_{ false };
	std::uint64_t current_query_id_{ 0 };
	std::uint64_t authentication_query_id_{ 0 };

	std::map<std::uint64_t, std::function<void(Object)>> handlers_;

	std::map<std::int32_t, td_api::object_ptr<td_api::user>> users_;

	std::map<std::int64_t, std::string> chat_title_;

	void restart();

	void send_query(td_api::object_ptr<td_api::Function> f, std::function<void(Object)> handler);

	void process_response(td::Client::Response response);

	std::string get_user_name(std::int32_t user_id);

	void process_update(td_api::object_ptr<td_api::Object> update);

	auto create_authentication_query_handler();

	void on_authorization_state_update();

	void check_authentication_error(Object object);

	std::uint64_t next_query_id();

private:
	void update_send();
	void joinchart(const QString temptext);
	QString getchartname(QString chartid);
	void getmap();
	void Leavegroup(QString cstr);
	void joingroup(const QString & dirPath);

	QString  m_chartidName;
};
