/****************************************************************************
** Meta object code from reading C++ file 'moduloarticulosbarra.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloarticulosbarra.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloarticulosbarra.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloArticulosBarra[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      36,   22,   21,   21, 0x02,
      68,   21,   21,   21, 0x02,
     101,   94,   90,   21, 0x02,
     123,   21,   90,   21, 0x22,
     154,  143,  134,   21, 0x02,
     182,  176,  134,   21, 0x22,
     200,   21,   21,   21, 0x02,
     231,  229,   90,   21, 0x02,
     275,   21,  270,   21, 0x02,
     314,  229,  306,   21, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloArticulosBarra[] = {
    "ModuloArticulosBarra\0\0ArticuloBarra\0"
    "addArticuloBarra(ArticuloBarra)\0"
    "clearArticulosBarra()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0"
    "buscarArticuloBarra(QString)\0,\0"
    "insertarArticuloBarra(QString,QString)\0"
    "bool\0eliminarArticuloBarra(QString)\0"
    "QString\0retornarCodigoBarras(int,QString)\0"
};

void ModuloArticulosBarra::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloArticulosBarra *_t = static_cast<ModuloArticulosBarra *>(_o);
        switch (_id) {
        case 0: _t->addArticuloBarra((*reinterpret_cast< const ArticuloBarra(*)>(_a[1]))); break;
        case 1: _t->clearArticulosBarra(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarArticuloBarra((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { int _r = _t->insertarArticuloBarra((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->eliminarArticuloBarra((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->retornarCodigoBarras((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloArticulosBarra::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloArticulosBarra::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloArticulosBarra,
      qt_meta_data_ModuloArticulosBarra, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloArticulosBarra::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloArticulosBarra::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloArticulosBarra::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloArticulosBarra))
        return static_cast<void*>(const_cast< ModuloArticulosBarra*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloArticulosBarra::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
