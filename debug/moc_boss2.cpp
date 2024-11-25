/****************************************************************************
** Meta object code from reading C++ file 'boss2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../boss2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'boss2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Boss2_t {
    QByteArrayData data[9];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Boss2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Boss2_t qt_meta_stringdata_Boss2 = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Boss2"
QT_MOC_LITERAL(1, 6, 5), // "begin"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 24), // "QList<makeEnemyBullet*>*"
QT_MOC_LITERAL(4, 38, 12), // "enemyBullets"
QT_MOC_LITERAL(5, 51, 5), // "start"
QT_MOC_LITERAL(6, 57, 4), // "stop"
QT_MOC_LITERAL(7, 62, 5), // "pause"
QT_MOC_LITERAL(8, 68, 8) // "Continue"

    },
    "Boss2\0begin\0\0QList<makeEnemyBullet*>*\0"
    "enemyBullets\0start\0stop\0pause\0Continue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Boss2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Boss2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Boss2 *_t = static_cast<Boss2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->begin((*reinterpret_cast< QList<makeEnemyBullet*>*(*)>(_a[1]))); break;
        case 1: _t->start(); break;
        case 2: _t->stop(); break;
        case 3: _t->pause(); break;
        case 4: _t->Continue(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Boss2::*_t)(QList<makeEnemyBullet*> * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Boss2::begin)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Boss2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Boss2::start)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Boss2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Boss2::stop)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Boss2::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Boss2.data,
      qt_meta_data_Boss2,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Boss2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Boss2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Boss2.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Boss2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Boss2::begin(QList<makeEnemyBullet*> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Boss2::start()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Boss2::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
