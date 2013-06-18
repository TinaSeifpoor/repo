/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Jun 16 12:04:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
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
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x05,
      41,   34,   11,   11, 0x05,
      74,   63,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     105,  100,   11,   11, 0x0a,
     124,  122,   11,   11, 0x0a,
     147,  145,   11,   11, 0x0a,
     172,  168,   11,   11, 0x0a,
     213,   11,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     290,  284,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0im\0showImage(cv::Mat)\0"
    "forest\0loadForest(QFileInfo)\0imageFiles\0"
    "testForest(QFileInfoList)\0text\0"
    "showLog(QString)\0c\0showLog(const char*)\0"
    "s\0showLog(std::string)\0hfe\0"
    "evaluation(QList<HoughForestEvaluation>)\0"
    "on_pushButtonLoadForest_released()\0"
    "on_pushButtonSelectImage_released()\0"
    "index\0on_listViewLoadedImages_entered(QModelIndex)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->showImage((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 1: _t->loadForest((*reinterpret_cast< QFileInfo(*)>(_a[1]))); break;
        case 2: _t->testForest((*reinterpret_cast< QFileInfoList(*)>(_a[1]))); break;
        case 3: _t->showLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->showLog((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 5: _t->showLog((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->evaluation((*reinterpret_cast< QList<HoughForestEvaluation>(*)>(_a[1]))); break;
        case 7: _t->on_pushButtonLoadForest_released(); break;
        case 8: _t->on_pushButtonSelectImage_released(); break;
        case 9: _t->on_listViewLoadedImages_entered((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showImage(cv::Mat _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::loadForest(QFileInfo _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::testForest(QFileInfoList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
