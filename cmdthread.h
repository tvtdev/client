#pragma once

#include <QThread>
#include <QDebug>
#include <QTextStream>
#include <QTimer>

#include <td/telegram/Client.h>
#include <td/telegram/Log.h>
#include <td/telegram/td_api.h>
#include <td/telegram/td_api.hpp>
namespace td_api = td::td_api;
using Object = td_api::object_ptr<td_api::Object>;
using Handler = std::function<void(Object)>;
class CmdThread : public QThread
{
	Q_OBJECT

  public:
	CmdThread(QObject *parent = nullptr);
	~CmdThread();
  signals:
	void execCommand(QString command,Handler handler={});
  public slots:
	void getCommand();

  protected:
	virtual void run() override;
};
