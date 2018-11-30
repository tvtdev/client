#include "logout.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <unistd.h>
LogOut* LogOut::m_object;
QMutex LogOut::m_mutex;
LogOut::ReleaseObject LogOut::m_releaseObject;

LogOut::LogOut()
    : m_maxLine(1000)
    , m_lineBreakSymbol("\r\n")
    , m_fileName("")
{
}

LogOut::~LogOut()
{
	m_fileObj.flush();
	fsync(m_fileObj.handle());
    m_fileObj.close();
}

QString LogOut::getFileName() const
{
    return m_fileName;
}

void LogOut::setFileName(QString val)
{
    m_fileName = val;

    //读取文件中已有信息到队列中.
    m_fileObj.setFileName(m_fileName);
    if (m_fileObj.exists(m_fileName))
    {
        m_fileObj.open(QIODevice::ReadOnly);
        QByteArray fileDataTemp = m_fileObj.readAll();
        QString fileData(fileDataTemp);


		if (fileData.size() != 0)
			QStringList2LogQueue(fileData, "\r\n");

		m_fileObj.flush();
		fsync(m_fileObj.handle());
		m_fileObj.close();

    }
}

int LogOut::getMaxLine() const
{
    return m_maxLine;
}

void LogOut::setMaxLine(int val)
{
    m_maxLine = val;
}

QString LogOut::getLineBreakSymbol() const
{
    return m_lineBreakSymbol;
}

void LogOut::setLineBreakSymbol(QString val)
{
    m_lineBreakSymbol = val;
}

void LogOut::printLog(const QString& logData)
{
    if (logData.size() != 0 && !(m_fileObj.fileName().isEmpty()))
    {
		//处理日志信息并存储至队列中
		QStringList2LogQueue(logData, m_lineBreakSymbol);
        if (m_fileObj.open(QIODevice::Truncate | QIODevice::WriteOnly))
        {
			//输出到文件;
			QTextStream outStream(&m_fileObj);
			QStringList::iterator listIt = m_logQueue.begin();
			while (listIt != m_logQueue.end())
			{
				QString temp = listIt->trimmed();
				outStream << temp << "\r\n";
				++listIt;
			}
        }
		m_fileObj.flush();
		fsync(m_fileObj.handle());
        m_fileObj.close();

		m_logQueue.clear();
    }   
}

LogOut* LogOut::GetInstance()
{
    if (m_object == nullptr)
    {
        m_mutex.lock();
        if (m_object == nullptr)
        {
            m_object = new LogOut;
        }
        m_mutex.unlock();
    }
    return m_object;
}

void LogOut::operator<<(const QString& logData)
{
    printLog(logData);
}


void LogOut::QStringList2LogMap(const QString & logData, const QString & lineBreakSymbol)
{
	QString logDatatemp = logData.trimmed();
	QStringList temp = logDatatemp.split(lineBreakSymbol);

	QStringList::const_iterator it = temp.begin();

	if (logData.indexOf("-") != -1)
	{
		while (it != temp.end())
		{
			QString line = (*it);

			QStringList linetemp = line.split("-");
			QString line_str = linetemp.at(0);
			int line_count = 0;
			if (linetemp.size() == 2)
				line_count = linetemp.at(1).toInt();

			m_logMap[line_str] = line_count;
			
			++it;
		}
	}

}

void LogOut::QStringList2LogQueue(const QString & logData ,const QString & lineBreakSymbol)
{
	QString logDatatemp = logData.trimmed();
	QStringList temp = logDatatemp.split(lineBreakSymbol);

	QStringList::const_iterator it = temp.begin();
	while (it != temp.end())
	{
		if (!m_logQueue.contains(*it))
		{
			m_logQueue << (*it);
			if (m_logQueue.size() > m_maxLine)
			{
				m_logQueue.pop_front();
			}
		}
		++it;
	}
}
