////////////////////////////////////////////////////////////////////////////
//单例类，可直接移植至包含qt开发环境的工程中使用（线程安全）
////////////////////////////////////////////////////////////////////////////
#ifndef LOGOUT_H__
#define LOGOUT_H__

#include <QObject>
#include <QMutex>
#include <QFile>
#include <QMap>

class LogOut
{
protected:
    LogOut();
    ~LogOut();
protected:
    //用来在程序结束时，释放单例变量内存
    class ReleaseObject
    {
    public:
        ~ReleaseObject()
        {
            if (m_object != nullptr)
            {
                delete m_object;
                m_object = nullptr;
            }
        }
    };
public:
    /**
     * @brief        获取日志文件名称 
     * @param[out]   None
     * @return  
     * @author       2018.11.12      
     */
    QString getFileName() const;
    /**
     * @brief        设置日志文件名称
     * @param[in]    QString val
     * @param[out]   None
     * @return  
     * @author       2018.11.12      
     */
    void setFileName(QString val);
    /**
     * @brief        获取最大行数;
     * @param[out]   None
     * @return       日志文件最大行数;
     * @author       2018.11.12      
     */
    int getMaxLine() const;
    /**
     * @brief        设置最大行数;
     * @param[in]    int val
     * @param[out]   None
     * @return  
     * @author       2018.11.12      
     */
    void setMaxLine(int val);

    /**
     * @brief        获取换行标记
     * @param[out]   None
     * @return  
     * @author       2018.11.12      
     */
    QString getLineBreakSymbol() const;
    /**
     * @brief        设置换行标记
     * @param[in]    QString val
     * @param[out]   None
     * @return  
     * @author       2018.11.12      
     */
    void setLineBreakSymbol(QString val);

    /**
     * @brief        打印日志信息
     * @param[in]    const QString & logData
     * @param[out]   None
     * @return  
     * @author       2018.11.12      
     */
    void printLog(const QString& logData);

    static LogOut* GetInstance();

public:
    /**
     * @brief        重载定向输出符号
     * @param[in]    const QString & logData 日志信息
     * @param[out]   None
     * @return
     * @author       2018.11.12
     */
    void operator <<(const QString& logData);
protected:
    /**
     * @brief        处理日志信息，并存储至队列中
     * @param[in]    const QString & logData 日志信息
     *               const QString & symbol  分割符号（日志输出时，分割符号统一为"\r\n"，输入可自定义）
     * @param[out]   None
     * @return
     * @author       2018.11.12
     */
    void QStringList2LogQueue(const QString & logData, const QString & symbol);
	void QStringList2LogMap(const QString & logData, const QString & symbol);

protected:
    QMap<QString,int>     m_logMap;         //每一个节点表示文件中的一行，最大长度不超过m_maxLine;
	QStringList     m_logQueue;         //每一个节点表示文件中的一行，最大长度不超过m_maxLine;


    int             m_maxLine;          //最大行数;
    QString         m_lineBreakSymbol;  //换行标记
    QString         m_fileName;         //文件全路径
    QFile           m_fileObj;          //文件操作对象
    static LogOut*  m_object;           //单例类对象
    static QMutex   m_mutex;            //线程锁，保证调用安全性.
    static ReleaseObject m_releaseObject;
};

#endif // LOGOUT_H__
