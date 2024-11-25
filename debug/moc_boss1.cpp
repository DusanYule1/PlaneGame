/****************************************************************************
** Meta object code from reading C++ file 'boss1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../boss1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'boss1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Boss1_t {
    QByteArrayData data[12];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Boss1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Boss1_t qt_meta_stringdata_Boss1 = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Boss1"
QT_MOC_LITERAL(1, 6, 4), // "lock"
QT_MOC_LITERAL(2, 11, 0), // ""
QT_MOC_LITERAL(3, 12, 1), // "x"
QT_MOC_LITERAL(4, 14, 1), // "y"
QT_MOC_LITERAL(5, 16, 24), // "QList<makeEnemyBullet*>*"
QT_MOC_LITERAL(6, 41, 12), // "enemyBullets"
QT_MOC_LITERAL(7, 54, 4), // "stop"
QT_MOC_LITERAL(8, 59, 5), // "start"
QT_MOC_LITERAL(9, 65, 8), // "moveBoss"
QT_MOC_LITERAL(10, 74, 5), // "pause"
QT_MOC_LITERAL(11, 80, 8) // "Continue"

    },
    "Boss1\0lock\0\0x\0y\0QList<makeEnemyBullet*>*\0"
    "enemyBullets\0stop\0start\0moveBoss\0pause\0"
    "Continue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Boss1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,
       7,    0,   51,    2, 0x06 /* Public */,
       8,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   53,    2, 0x0a /* Public */,
      10,    0,   54,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Boss1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Boss1 *_t = static_cast<Boss1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QList<makeEnemyBullet*>*(*)>(_a[3]))); break;
        case 1: _t->stop(); break;
        case 2: _t->start(); break;
        case 3: _t->moveBoss(); break;
        case 4: _t->pause(); break;
        case 5: _t->Continue(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Boss1::*_t)(int , int , QList<makeEnemyBullet*> * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Boss1::lock)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Boss1::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Boss1::stop)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Boss1::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Boss1::start)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Boss1::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Boss1.data,
      qt_meta_data_Boss1,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Boss1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Boss1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Boss1.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Boss1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Boss1::lock(int _t1, int _t2, QList<makeEnemyBullet*> * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Boss1::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Boss1::start()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
