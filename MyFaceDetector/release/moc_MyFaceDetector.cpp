/****************************************************************************
** Meta object code from reading C++ file 'MyFaceDetector.h'
**
** Created: Sun Jun 16 12:00:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MyFaceDetector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyFaceDetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyFaceDetector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   57,   15,   15, 0x0a,
      97,   86,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyFaceDetector[] = {
    "MyFaceDetector\0\0"
    "evaluation(QList<HoughForestEvaluation>)\0"
    "forest\0loadForest(QFileInfo)\0imageFiles\0"
    "testForest(QFileInfoList)\0"
};

void MyFaceDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyFaceDetector *_t = static_cast<MyFaceDetector *>(_o);
        switch (_id) {
        case 0: _t->evaluation((*reinterpret_cast< QList<HoughForestEvaluation>(*)>(_a[1]))); break;
        case 1: _t->loadForest((*reinterpret_cast< QFileInfo(*)>(_a[1]))); break;
        case 2: _t->testForest((*reinterpret_cast< QFileInfoList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyFaceDetector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyFaceDetector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyFaceDetector,
      qt_meta_data_MyFaceDetector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyFaceDetector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyFaceDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyFaceDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyFaceDetector))
        return static_cast<void*>(const_cast< MyFaceDetector*>(this));
    return QObject::qt_metacast(_clname);
}

int MyFaceDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyFaceDetector::evaluation(QList<HoughForestEvaluation> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
