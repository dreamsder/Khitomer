/****************************************************************************
** Meta object code from reading C++ file 'modulotipoprocedenciacliente.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulotipoprocedenciacliente.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulotipoprocedenciacliente.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloTipoProcedenciaCliente[] = {

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
      53,   30,   29,   29, 0x02,
      81,   29,   29,   29, 0x02,
     102,   95,   91,   29, 0x02,
     124,   29,   91,   29, 0x22,
     155,  144,  135,   29, 0x02,
     183,  177,  135,   29, 0x22,
     203,  201,   29,   29, 0x02,
     227,   29,   29,   29, 0x02,
     244,   29,  236,   29, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloTipoProcedenciaCliente[] = {
    "ModuloTipoProcedenciaCliente\0\0"
    "TipoProcedenciaCliente\0"
    "add(TipoProcedenciaCliente)\0limpiar()\0"
    "int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0QVariant\0index,role\0"
    "data(QModelIndex,int)\0index\0"
    "data(QModelIndex)\0,\0buscar(QString,QString)\0"
    "buscar()\0QString\0"
    "retornaDescripcionTipoProcedenciaCliente(QString)\0"
};

void ModuloTipoProcedenciaCliente::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloTipoProcedenciaCliente *_t = static_cast<ModuloTipoProcedenciaCliente *>(_o);
        switch (_id) {
        case 0: _t->add((*reinterpret_cast< const TipoProcedenciaCliente(*)>(_a[1]))); break;
        case 1: _t->limpiar(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscar((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->buscar(); break;
        case 8: { QString _r = _t->retornaDescripcionTipoProcedenciaCliente((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloTipoProcedenciaCliente::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloTipoProcedenciaCliente::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloTipoProcedenciaCliente,
      qt_meta_data_ModuloTipoProcedenciaCliente, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloTipoProcedenciaCliente::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloTipoProcedenciaCliente::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloTipoProcedenciaCliente::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloTipoProcedenciaCliente))
        return static_cast<void*>(const_cast< ModuloTipoProcedenciaCliente*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloTipoProcedenciaCliente::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
