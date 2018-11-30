#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "telegramthread.h"
#include "cmdthread.h"
#include "loger.h"
#define LOG_FILE
void loggerOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	QString logMsg = "[%1][%2][%3]-%4\n";
	logMsg = logMsg.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
		.arg(type == QtDebugMsg ? "INFO" : type == QtWarningMsg ? "WARNING" : "ERROR")
		.arg(QFileInfo(context.file).baseName() + QString(":") + QString::number(context.line) ).arg(msg);
	Loger *logger = Loger::getInstance();
	logger->writeLog(logMsg);

}
int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);
	Loger::getInstance();
#ifdef LOG_FILE
	qInstallMessageHandler(loggerOutput);
#endif // _RELEASE
//	QTextStream tin(stdin);
//	QString dbPassword="123123", phoneNumber="+8618980505174", firstName="hu", lastName="mm";
  //      std::cerr << "Input SQLITE db password:";
//	tin >> dbPassword;
//	std::cerr <<"Input phone number(include +):";
//	tin >> phoneNumber;
//	std::cerr <<"Input first name:";
//	tin >> firstName;
//	std::cerr <<"Input last name:";
//	tin >> lastName;
	CmdThread cmdThread;
	TelegramThread tgThread;
	QObject::connect(&tgThread, &TelegramThread::authSuccess, [&]() {
		cmdThread.start();
	});
	QObject::connect(&cmdThread, &CmdThread::execCommand, &tgThread, &TelegramThread::execCommand, Qt::QueuedConnection);
//	tgThread.dbPassword = dbPassword; tgThread.phoneNumber = phoneNumber, tgThread.firstName = firstName, tgThread.lastName = lastName;
	tgThread.start();
	return a.exec();
}
