/****************************************************************************
** Meta object code from reading C++ file 'modulocuentasbancarias.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulocuentasbancarias.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulocuentasbancarias.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloCuentasBancarias[] = {

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

 // methods: signature, parameters, type, tag, flags
      41,   24,   23,   23, 0x02,
      81,   23,   23,   23, 0x02,
     123,  116,  112,   23, 0x02,
     145,   23,  112,   23, 0x22,
     176,  165,  156,   23, 0x02,
     204,  198,  156,   23, 0x22,
     224,  222,   23,   23, 0x02,
     269,  222,  264,   23, 0x02,
     313,  309,  112,   23, 0x02,
     377,   23,  369,   23, 0x02,
     418,   23,  369,   23, 0x02,
     457,  454,  369,   23, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloCuentasBancarias[] = {
    "ModuloCuentasBancarias\0\0CuentasBancarias\0"
    "agregarCuentaBancaria(CuentasBancarias)\0"
    "limpiarListaCuentasBancarias()\0int\0"
    "parent\0rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarCuentasBancarias(QString,QString)\0"
    "bool\0eliminarCuentaBancaria(QString,QString)\0"
    ",,,\0insertarCuentaBancaria(QString,QString,QString,QString)\0"
    "QString\0retornaPrimeraCuentaBancariaDisponible()\0"
    "retornaBancoCuentaBancaria(QString)\0"
    ",,\0retornaTotalXMonedaCuentaBancaria(QString,QString,QString)\0"
};

void ModuloCuentasBancarias::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloCuentasBancarias *_t = static_cast<ModuloCuentasBancarias *>(_o);
        switch (_id) {
        case 0: _t->agregarCuentaBancaria((*reinterpret_cast< const CuentasBancarias(*)>(_a[1]))); break;
        case 1: _t->limpiarListaCuentasBancarias(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarCuentasBancarias((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { bool _r = _t->eliminarCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->insertarCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->retornaPrimeraCuentaBancariaDisponible();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaBancoCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaTotalXMonedaCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloCuentasBancarias::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloCuentasBancarias::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloCuentasBancarias,
      qt_meta_data_ModuloCuentasBancarias, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloCuentasBancarias::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloCuentasBancarias::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloCuentasBancarias::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloCuentasBancarias))
        return static_cast<void*>(const_cast< ModuloCuentasBancarias*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloCuentasBancarias::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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
