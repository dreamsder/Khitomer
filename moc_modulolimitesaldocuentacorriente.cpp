/****************************************************************************
** Meta object code from reading C++ file 'modulolimitesaldocuentacorriente.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulolimitesaldocuentacorriente.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulolimitesaldocuentacorriente.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloLimiteSaldoCuentaCorriente[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      61,   34,   33,   33, 0x02,
      97,   33,   33,   33, 0x02,
     118,  111,  107,   33, 0x02,
     140,   33,  107,   33, 0x22,
     171,  160,  151,   33, 0x02,
     199,  193,  151,   33, 0x22,
     245,  217,   33,   33, 0x02,
     285,  281,  269,   33, 0x02,
     349,  294,  107,   33, 0x02,
     441,  399,  391,   33, 0x02,
     485,  399,  480,   33, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloLimiteSaldoCuentaCorriente[] = {
    "ModuloLimiteSaldoCuentaCorriente\0\0"
    "limiteSaldoCuentaCorriente\0"
    "agregar(LimiteSaldoCuentaCorriente)\0"
    "limpiar()\0int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0QVariant\0index,role\0"
    "data(QModelIndex,int)\0index\0"
    "data(QModelIndex)\0_codigoCliente,_tipoCliente\0"
    "buscar(QString,QString)\0QVariantMap\0"
    "row\0get(int)\0"
    "_codigoCliente,_tipoCliente,_codigoMoneda,_limiteSaldo\0"
    "insertar(QString,QString,QString,QString)\0"
    "QString\0_codigoCliente,_tipoCliente,_codigoMoneda\0"
    "retornarSaldo(QString,QString,QString)\0"
    "bool\0tieneSaldoConfigurado(QString,QString,QString)\0"
};

void ModuloLimiteSaldoCuentaCorriente::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloLimiteSaldoCuentaCorriente *_t = static_cast<ModuloLimiteSaldoCuentaCorriente *>(_o);
        switch (_id) {
        case 0: _t->agregar((*reinterpret_cast< const LimiteSaldoCuentaCorriente(*)>(_a[1]))); break;
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
        case 7: { QVariantMap _r = _t->get((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->insertar((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->retornarSaldo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->tieneSaldoConfigurado((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloLimiteSaldoCuentaCorriente::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloLimiteSaldoCuentaCorriente::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloLimiteSaldoCuentaCorriente,
      qt_meta_data_ModuloLimiteSaldoCuentaCorriente, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloLimiteSaldoCuentaCorriente::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloLimiteSaldoCuentaCorriente::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloLimiteSaldoCuentaCorriente::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloLimiteSaldoCuentaCorriente))
        return static_cast<void*>(const_cast< ModuloLimiteSaldoCuentaCorriente*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloLimiteSaldoCuentaCorriente::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
