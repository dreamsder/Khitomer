/****************************************************************************
** Meta object code from reading C++ file 'modulotarjetascredito.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulotarjetascredito.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulotarjetascredito.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloTarjetasCredito[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      39,   23,   22,   22, 0x02,
      78,   22,   22,   22, 0x02,
     119,  112,  108,   22, 0x02,
     141,   22,  108,   22, 0x22,
     172,  161,  152,   22, 0x02,
     200,  194,  152,   22, 0x22,
     220,  218,   22,   22, 0x02,
     267,   22,  259,   22, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloTarjetasCredito[] = {
    "ModuloTarjetasCredito\0\0TarjetasCredito\0"
    "agregarTarjetaCredito(TarjetasCredito)\0"
    "limpiarListaTarjetasCredito()\0int\0"
    "parent\0rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarTarjetasCredito(QString,QString)\0"
    "QString\0retornaDescripcionTarjetaCredito(QString)\0"
};

void ModuloTarjetasCredito::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloTarjetasCredito *_t = static_cast<ModuloTarjetasCredito *>(_o);
        switch (_id) {
        case 0: _t->agregarTarjetaCredito((*reinterpret_cast< const TarjetasCredito(*)>(_a[1]))); break;
        case 1: _t->limpiarListaTarjetasCredito(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarTarjetasCredito((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionTarjetaCredito((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloTarjetasCredito::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloTarjetasCredito::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloTarjetasCredito,
      qt_meta_data_ModuloTarjetasCredito, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloTarjetasCredito::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloTarjetasCredito::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloTarjetasCredito::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloTarjetasCredito))
        return static_cast<void*>(const_cast< ModuloTarjetasCredito*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloTarjetasCredito::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
