#include "cmdthread.h"

CmdThread::CmdThread(QObject *parent)
	: QThread(parent)
{
	moveToThread(this);
	connect(this, &CmdThread::started, this, &CmdThread::getCommand, Qt::UniqueConnection);
}

CmdThread::~CmdThread()
{
}
#include <iostream>
void CmdThread::getCommand()
{
	QTextStream tin(stdin);
	QString cmd = "";
	std::cerr << "Enter action [q] quit [u] check for updates and request results [c] show chats [m <id> <text>] "
		        "send message  [j <group invite link>] join group [g <id>] leave group  [l] logout: "
					<< std::endl;
	    qDebug() << "Enter action [q] quit [u] check for updates and request results [c] show chats [m <id> <text>] send message  [j <group invite link>] join group [g <id>] leave group  [l] logout: ";
	tin.readLineInto(&cmd);
	if(!cmd.isEmpty())
		emit execCommand(cmd.toUtf8());
	QTimer::singleShot(1000, this, &CmdThread::getCommand);
}

void CmdThread::run()
{
	exec();
}
