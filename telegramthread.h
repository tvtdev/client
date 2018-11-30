#pragma once

#include <QThread>
#include <QDebug>
#include "tdclient.h"
class TelegramThread : public QThread
{
	Q_OBJECT

public:
	TelegramThread(QObject *parent=nullptr);
	~TelegramThread();
	QString dbPassword, phoneNumber, firstName, lastName;
signals:
	void sendMessage(std::int64_t chat_id, std::string text);
	void loadChatList();
	void authSuccess();
	void execCommand(QString cmd);
private slots:
	void chatListHandler(QList<Chat> chats);
	void newMessageHandler(qint64 chatId, QString senderName, QString content);
protected:
	virtual void run() override;
private:
	TdClient * m_tgClient = nullptr;
	
};
