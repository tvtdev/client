/****************************************************************************
** Meta object code from reading C++ file 'telegramthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "telegramthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'telegramthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TelegramThread_t {
    QByteArrayData data[18];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TelegramThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TelegramThread_t qt_meta_stringdata_TelegramThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TelegramThread"
QT_MOC_LITERAL(1, 15, 11), // "sendMessage"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "std::int64_t"
QT_MOC_LITERAL(4, 41, 7), // "chat_id"
QT_MOC_LITERAL(5, 49, 11), // "std::string"
QT_MOC_LITERAL(6, 61, 4), // "text"
QT_MOC_LITERAL(7, 66, 12), // "loadChatList"
QT_MOC_LITERAL(8, 79, 11), // "authSuccess"
QT_MOC_LITERAL(9, 91, 11), // "execCommand"
QT_MOC_LITERAL(10, 103, 3), // "cmd"
QT_MOC_LITERAL(11, 107, 15), // "chatListHandler"
QT_MOC_LITERAL(12, 123, 11), // "QList<Chat>"
QT_MOC_LITERAL(13, 135, 5), // "chats"
QT_MOC_LITERAL(14, 141, 17), // "newMessageHandler"
QT_MOC_LITERAL(15, 159, 6), // "chatId"
QT_MOC_LITERAL(16, 166, 10), // "senderName"
QT_MOC_LITERAL(17, 177, 7) // "content"

    },
    "TelegramThread\0sendMessage\0\0std::int64_t\0"
    "chat_id\0std::string\0text\0loadChatList\0"
    "authSuccess\0execCommand\0cmd\0chatListHandler\0"
    "QList<Chat>\0chats\0newMessageHandler\0"
    "chatId\0senderName\0content"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TelegramThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       7,    0,   49,    2, 0x06 /* Public */,
       8,    0,   50,    2, 0x06 /* Public */,
       9,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   54,    2, 0x08 /* Private */,
      14,    3,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString, QMetaType::QString,   15,   16,   17,

       0        // eod
};

void TelegramThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TelegramThread *_t = static_cast<TelegramThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< std::int64_t(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 1: _t->loadChatList(); break;
        case 2: _t->authSuccess(); break;
        case 3: _t->execCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->chatListHandler((*reinterpret_cast< QList<Chat>(*)>(_a[1]))); break;
        case 5: _t->newMessageHandler((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<Chat> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TelegramThread::*_t)(std::int64_t , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelegramThread::sendMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TelegramThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelegramThread::loadChatList)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TelegramThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelegramThread::authSuccess)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TelegramThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelegramThread::execCommand)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TelegramThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TelegramThread.data,
      qt_meta_data_TelegramThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TelegramThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TelegramThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TelegramThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TelegramThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TelegramThread::sendMessage(std::int64_t _t1, std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TelegramThread::loadChatList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TelegramThread::authSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TelegramThread::execCommand(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
