/****************************************************************************
** Meta object code from reading C++ file 'modulotipoclasificacion.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulotipoclasificacion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulotipoclasificacion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloTipoClasificacion[] = {

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
      45,   25,   24,   24, 0x02,
      87,   24,   24,   24, 0x02,
     123,  116,  112,   24, 0x02,
     145,   24,  112,   24, 0x22,
     176,  165,  156,   24, 0x02,
     204,  198,  156,   24, 0x22,
     224,  222,   24,   24, 0x02,
     273,   24,  265,   24, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloTipoClasificacion[] = {
    "ModuloTipoClasificacion\0\0TipoDeClasificacion\0"
    "addTipoClasificacion(TipoDeClasificacion)\0"
    "clearTipoClasificacion()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarTipoClasificacion(QString,QString)\0"
    "QString\0primerRegistroDeTipoClasificacionEnBase()\0"
};

void ModuloTipoClasificacion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloTipoClasificacion *_t = static_cast<ModuloTipoClasificacion *>(_o);
        switch (_id) {
        case 0: _t->addTipoClasificacion((*reinterpret_cast< const TipoDeClasificacion(*)>(_a[1]))); break;
        case 1: _t->clearTipoClasificacion(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarTipoClasificacion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->primerRegistroDeTipoClasificacionEnBase();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloTipoClasificacion::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloTipoClasificacion::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloTipoClasificacion,
      qt_meta_data_ModuloTipoClasificacion, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloTipoClasificacion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloTipoClasificacion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloTipoClasificacion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloTipoClasificacion))
        return static_cast<void*>(const_cast< ModuloTipoClasificacion*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloTipoClasificacion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
