#include "telegramthread.h"
#include <QTimer>
TelegramThread::TelegramThread(QObject *parent)
	: QThread(parent)
{
	moveToThread(this);
}

TelegramThread::~TelegramThread()
{
}

void TelegramThread::chatListHandler(QList<Chat> chats)
{
	qDebug() << "Chat list length:" << chats.count();
	foreach (auto chat, chats)
	{
		qDebug() << chat.id << ":" << chat.title;
	}
}

void TelegramThread::newMessageHandler(qint64 chatId, QString senderName, QString content)
{
	qDebug() << "Recv msg from " << senderName<<" chat id is "<<chatId<<" content is "<<content;
}

void TelegramThread::run()
{
	if (m_tgClient == nullptr) {
		m_tgClient = new TdClient();
		connect(m_tgClient, &TdClient::chatListResult, this, &TelegramThread::chatListHandler, Qt::UniqueConnection);
		connect(m_tgClient, &TdClient::newMessage, this, &TelegramThread::newMessageHandler, Qt::UniqueConnection);
		connect(m_tgClient, &TdClient::authSuccess, this, &TelegramThread::authSuccess, Qt::UniqueConnection);
		connect(this, &TelegramThread::loadChatList, m_tgClient, &TdClient::loadChatList, Qt::UniqueConnection);
		connect(this, &TelegramThread::sendMessage, m_tgClient, &TdClient::sendMessage, Qt::UniqueConnection);
		connect(this, &TelegramThread::execCommand, m_tgClient, &TdClient::execCommand, Qt::UniqueConnection);
		m_tgClient->dbPassword = dbPassword.toUtf8().data();
		m_tgClient->phoneNumber = phoneNumber.toUtf8().data();
		m_tgClient->firstName = firstName.toUtf8().data();
		m_tgClient->lastName = lastName.toUtf8().data();
	}
	m_tgClient->loop();
	QTimer timer,switchUserTimer;
	timer.setInterval(1000);
	switchUserTimer.setInterval(1000*60*10);
	connect(&timer, &QTimer::timeout, [&] {
		m_tgClient->update();
	});
	connect(&switchUserTimer, &QTimer::timeout, [&] {
		m_tgClient->restart();
	});
    QTimer::singleShot(1000, [&]() {
		m_tgClient->loadChatList();
		timer.start();
	});
	
	
	exec();
}
