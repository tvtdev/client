#include "loger.h"
#include <QCoreApplication>

#define GLOBALVAR_LOG_PATH "/home/ubuntu/src/build/"
Loger::Loger(QObject *parent)
	: QObject(parent), m_file(nullptr), m_ts(nullptr)
{
	updateLogFileName();
}

void Loger::removeDepressedLogFiles()
{
	return;
	QDir _dir(GLOBALVAR_LOG_PATH);
	QDate _currentDate = QDate::currentDate();
	QFileInfoList _filesInfos = _dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
	for (int i = 0; i < _filesInfos.count(); ++i)
	{
		QFileInfo &_fileInfo = _filesInfos[i];
		QDate _fileDate = QDate::fromString(_fileInfo.baseName(), "yyyyMMdd");
		if (!_fileDate.isValid() && _fileDate.isNull())
		{
			qDebug() << "remove unloggable file " << _fileInfo.absoluteFilePath();
			QFile::remove(_fileInfo.absoluteFilePath());
		}
		else
		{
			if (_fileDate.daysTo(_currentDate) > 10)
			{
				qDebug() << "remove depressed log file " << _fileInfo.absoluteFilePath();
				QFile::remove(_fileInfo.absoluteFilePath());
			}
		}
	}
}

Loger::~Loger()
{
	if (m_file)
	{
		m_file->close();
		delete m_file;
	}
	if (m_ts)
	{
		delete m_ts;
	}
}
Loger * Loger::getInstance()
{
	static Loger *loger = new Loger(nullptr);
	return loger;
}

void Loger::writeLog(QString log)
{
	if (m_ts != nullptr)
	{
		*m_ts << log;
		m_ts->flush();
	}
}

void Loger::updateLogFileName()
{
	qDebug() << "Update log file name.";
	removeDepressedLogFiles();
	if (m_file)
	{
		m_file->close();
		delete m_file;
	}
	if (m_ts)
	{
		delete m_ts;
	}
	m_file = new QFile(QCoreApplication::applicationDirPath() + QString("/%2_%3_%1.log").arg(QDate::currentDate().toString("yyyy-MM-dd")).arg("").arg(""));
	if (!m_file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		qDebug() << "Open log file error,error:" << m_file->errorString();
		m_ts = nullptr;
	}
	else
	{
		m_ts = new QTextStream(m_file);
	}
}
