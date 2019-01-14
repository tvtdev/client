/****************************************************************************
** Meta object code from reading C++ file 'tdclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tdclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tdclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TdClient_t {
    QByteArrayData data[23];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TdClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TdClient_t qt_meta_stringdata_TdClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TdClient"
QT_MOC_LITERAL(1, 9, 14), // "chatListResult"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "QList<Chat>"
QT_MOC_LITERAL(4, 37, 5), // "chats"
QT_MOC_LITERAL(5, 43, 10), // "newMessage"
QT_MOC_LITERAL(6, 54, 6), // "chatId"
QT_MOC_LITERAL(7, 61, 10), // "senderName"
QT_MOC_LITERAL(8, 72, 7), // "content"
QT_MOC_LITERAL(9, 80, 11), // "authSuccess"
QT_MOC_LITERAL(10, 92, 4), // "loop"
QT_MOC_LITERAL(11, 97, 6), // "logout"
QT_MOC_LITERAL(12, 104, 11), // "sendMessage"
QT_MOC_LITERAL(13, 116, 12), // "std::int64_t"
QT_MOC_LITERAL(14, 129, 7), // "chat_id"
QT_MOC_LITERAL(15, 137, 11), // "std::string"
QT_MOC_LITERAL(16, 149, 4), // "text"
QT_MOC_LITERAL(17, 154, 12), // "loadChatList"
QT_MOC_LITERAL(18, 167, 6), // "update"
QT_MOC_LITERAL(19, 174, 9), // "authorize"
QT_MOC_LITERAL(20, 184, 12), // "getUserInput"
QT_MOC_LITERAL(21, 197, 11), // "execCommand"
QT_MOC_LITERAL(22, 209, 3) // "cmd"

    },
    "TdClient\0chatListResult\0\0QList<Chat>\0"
    "chats\0newMessage\0chatId\0senderName\0"
    "content\0authSuccess\0loop\0logout\0"
    "sendMessage\0std::int64_t\0chat_id\0"
    "std::string\0text\0loadChatList\0update\0"
    "authorize\0getUserInput\0execCommand\0"
    "cmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TdClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    3,   72,    2, 0x06 /* Public */,
       9,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   80,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    2,   82,    2, 0x0a /* Public */,
      17,    0,   87,    2, 0x0a /* Public */,
      18,    0,   88,    2, 0x0a /* Public */,
      19,    0,   89,    2, 0x0a /* Public */,
      20,    0,   90,    2, 0x0a /* Public */,
      21,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString, QMetaType::QString,    6,    7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15,   14,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,

       0        // eod
};

void TdClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TdClient *_t = static_cast<TdClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->chatListResult((*reinterpret_cast< QList<Chat>(*)>(_a[1]))); break;
        case 1: _t->newMessage((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->authSuccess(); break;
        case 3: _t->loop(); break;
        case 4: _t->logout(); break;
        case 5: _t->sendMessage((*reinterpret_cast< std::int64_t(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 6: _t->loadChatList(); break;
        case 7: _t->update(); break;
        case 8: _t->authorize(); break;
        case 9: _t->getUserInput(); break;
        case 10: _t->execCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            typedef void (TdClient::*_t)(QList<Chat> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TdClient::chatListResult)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TdClient::*_t)(qint64 , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TdClient::newMessage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TdClient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TdClient::authSuccess)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TdClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TdClient.data,
      qt_meta_data_TdClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TdClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TdClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TdClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TdClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TdClient::chatListResult(QList<Chat> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TdClient::newMessage(qint64 _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TdClient::authSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
