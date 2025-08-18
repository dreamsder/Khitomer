/****************************************************************************
** Meta object code from reading C++ file 'modulolistaimpresoras.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulolistaimpresoras.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulolistaimpresoras.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloListaImpresoras[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      34,   23,   22,   22, 0x02,
      64,   22,   22,   22, 0x02,
     100,   93,   89,   22, 0x02,
     122,   22,   89,   22, 0x22,
     153,  142,  133,   22, 0x02,
     181,  175,  133,   22, 0x22,
     199,   22,   22,   22, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloListaImpresoras[] = {
    "ModuloListaImpresoras\0\0Impresoras\0"
    "agregarImpresoras(Impresoras)\0"
    "limpiarListaImpresoras()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0buscarImpresoras()\0"
};

void ModuloListaImpresoras::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloListaImpresoras *_t = static_cast<ModuloListaImpresoras *>(_o);
        switch (_id) {
        case 0: _t->agregarImpresoras((*reinterpret_cast< const Impresoras(*)>(_a[1]))); break;
        case 1: _t->limpiarListaImpresoras(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarImpresoras(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloListaImpresoras::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloListaImpresoras::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloListaImpresoras,
      qt_meta_data_ModuloListaImpresoras, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloListaImpresoras::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloListaImpresoras::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloListaImpresoras::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloListaImpresoras))
        return static_cast<void*>(const_cast< ModuloListaImpresoras*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloListaImpresoras::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
