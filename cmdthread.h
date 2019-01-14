#pragma once

#include <QThread>
#include <QDebug>
#include <QTextStream>
#include <QTimer>
class CmdThread : public QThread
{
	Q_OBJECT

public:
	CmdThread(QObject *parent = nullptr);
	~CmdThread();
signals:
	void execCommand(QString command);
public slots:
	void getCommand();
protected:
	virtual void run() override;

};
