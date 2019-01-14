#pragma once
#include <QObject>
struct Chat
{
	quint64 id;
	QString title;
};
Q_DECLARE_METATYPE(Chat)