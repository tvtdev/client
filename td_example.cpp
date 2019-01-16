#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "telegramthread.h"
#include "cmdthread.h"
#include "loger.h"
#define LOG_FILE
void loggerOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString logMsg = "[%1][%2][%3]-%4\n";
	logMsg = logMsg.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
				 .arg(type == QtDebugMsg ? "INFO" : type == QtWarningMsg ? "WARNING" : "ERROR")
				 .arg(QFileInfo(context.file).baseName() + QString(":") + QString::number(context.line))
				 .arg(msg);
	std::cerr << logMsg.toStdString();
#ifdef LOG_FILE
	Loger *logger = Loger::getInstance();
	logger->writeLog(logMsg);
#endif
}
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Loger::getInstance();
	qInstallMessageHandler(loggerOutput);
	QString phoneNumber = "";
	QCommandLineParser cmdParser;
	QCommandLineOption phoneOpt("phone");
	cmdParser.addOption(phoneOpt);
	cmdParser.process(a);
	phoneNumber = cmdParser.value(phoneOpt);
	if (phoneNumber.isEmpty())
	{
		//input phone number when no -phone arg specified
		QTextStream tin(stdin);
		tin >> phoneNumber;
	}
	CmdThread cmdThread;
	TelegramThread tgThread;
	tgThread.phoneNumber = phoneNumber;
	QObject::connect(&tgThread, &TelegramThread::authSuccess, [&]() {
		cmdThread.start();
	});
	QObject::connect(&cmdThread, &CmdThread::execCommand, &tgThread, &TelegramThread::execCommand, Qt::QueuedConnection);
	tgThread.start();
	return a.exec();
}
