/****************************************************************************
** Meta object code from reading C++ file 'SumoClient.h'
**
** Created: Wed 4. Jul 18:05:12 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SumoClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SumoClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SumoClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SumoClient[] = {
    "SumoClient\0\0newValue\0setStop(bool)\0"
};

void SumoClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SumoClient *_t = static_cast<SumoClient *>(_o);
        switch (_id) {
        case 0: _t->setStop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SumoClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SumoClient::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SumoClient,
      qt_meta_data_SumoClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SumoClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SumoClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SumoClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SumoClient))
        return static_cast<void*>(const_cast< SumoClient*>(this));
    return QThread::qt_metacast(_clname);
}

int SumoClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
