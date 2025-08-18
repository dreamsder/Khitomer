/****************************************************************************
** Meta object code from reading C++ file 'modulobusquedainteligente.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulobusquedainteligente.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulobusquedainteligente.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloBusquedaInteligente[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      47,   27,   26,   26, 0x02,
      95,   26,   26,   26, 0x02,
     135,  128,  124,   26, 0x02,
     157,   26,  124,   26, 0x22,
     188,  177,  168,   26, 0x02,
     216,  210,  168,   26, 0x22,
     236,  234,   26,   26, 0x02,
     277,   26,   26,   26, 0x02,
     312,   26,   26,   26, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloBusquedaInteligente[] = {
    "ModuloBusquedaInteligente\0\0"
    "BusquedaInteligente\0"
    "agregarBusquedaInteligente(BusquedaInteligente)\0"
    "limpiarBusquedaInteligente()\0int\0"
    "parent\0rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarArticulosInteligente(QString,bool)\0"
    "buscarClientesInteligente(QString)\0"
    "buscarProveedorInteligente(QString)\0"
};

void ModuloBusquedaInteligente::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloBusquedaInteligente *_t = static_cast<ModuloBusquedaInteligente *>(_o);
        switch (_id) {
        case 0: _t->agregarBusquedaInteligente((*reinterpret_cast< const BusquedaInteligente(*)>(_a[1]))); break;
        case 1: _t->limpiarBusquedaInteligente(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarArticulosInteligente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->buscarClientesInteligente((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->buscarProveedorInteligente((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloBusquedaInteligente::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloBusquedaInteligente::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloBusquedaInteligente,
      qt_meta_data_ModuloBusquedaInteligente, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloBusquedaInteligente::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloBusquedaInteligente::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloBusquedaInteligente::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloBusquedaInteligente))
        return static_cast<void*>(const_cast< ModuloBusquedaInteligente*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloBusquedaInteligente::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
