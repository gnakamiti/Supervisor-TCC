/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri 22. Jun 19:31:40 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      30,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     128,   11,   11,   11, 0x08,
     147,   11,   11,   11, 0x08,
     168,   11,   11,   11, 0x08,
     188,   11,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,
     234,   11,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     288,   11,  276,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0timeoutUpdateUI()\0"
    "listClick(QListWidgetItem*)\0"
    "listClickProgram(QListWidgetItem*)\0"
    "listClickStreets(QListWidgetItem*)\0"
    "phaseSelected(int)\0programSelected(int)\0"
    "initializeMap(bool)\0btnSendClick()\0"
    "btnCancelClick()\0btnNewClick()\0"
    "mainFrame_javaScriptWindowObjectCleared()\0"
    "QStringList\0getInformationForController(QString)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->timeoutUpdateUI(); break;
        case 1: _t->listClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->listClickProgram((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->listClickStreets((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->phaseSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->programSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->initializeMap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->btnSendClick(); break;
        case 8: _t->btnCancelClick(); break;
        case 9: _t->btnNewClick(); break;
        case 10: _t->mainFrame_javaScriptWindowObjectCleared(); break;
        case 11: { QStringList _r = _t->getInformationForController((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
