/****************************************************************************
** Meta object code from reading C++ file 'modulobancos.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulobancos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulobancos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloBancos[] = {

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
      21,   14,   13,   13, 0x02,
      42,   13,   13,   13, 0x02,
      74,   67,   63,   13, 0x02,
      96,   13,   63,   13, 0x22,
     127,  116,  107,   13, 0x02,
     155,  149,  107,   13, 0x22,
     175,  173,   13,   13, 0x02,
     213,   13,  205,   13, 0x02,
     246,  173,   63,   13, 0x02,
     282,   13,  277,   13, 0x02,
     305,   13,  205,   13, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloBancos[] = {
    "ModuloBancos\0\0Bancos\0agregarBanco(Bancos)\0"
    "limpiarListaBancos()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarBancos(QString,QString)\0QString\0"
    "retornaDescripcionBanco(QString)\0"
    "insertarBanco(QString,QString)\0bool\0"
    "eliminarBanco(QString)\0"
    "retornaUltimoCodigoBanco()\0"
};

void ModuloBancos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloBancos *_t = static_cast<ModuloBancos *>(_o);
        switch (_id) {
        case 0: _t->agregarBanco((*reinterpret_cast< const Bancos(*)>(_a[1]))); break;
        case 1: _t->limpiarListaBancos(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarBancos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionBanco((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->insertarBanco((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarBanco((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaUltimoCodigoBanco();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloBancos::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloBancos::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloBancos,
      qt_meta_data_ModuloBancos, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloBancos::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloBancos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloBancos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloBancos))
        return static_cast<void*>(const_cast< ModuloBancos*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloBancos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
