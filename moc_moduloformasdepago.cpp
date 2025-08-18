/****************************************************************************
** Meta object code from reading C++ file 'moduloformasdepago.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloformasdepago.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloformasdepago.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloFormasDePago[] = {

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
      32,   20,   19,   19, 0x02,
      64,   19,   19,   19, 0x02,
     101,   94,   90,   19, 0x02,
     123,   19,   90,   19, 0x22,
     154,  143,  134,   19, 0x02,
     182,  176,  134,   19, 0x22,
     202,  200,   19,   19, 0x02,
     245,   19,  237,   19, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloFormasDePago[] = {
    "ModuloFormasDePago\0\0FormaDePago\0"
    "agregarFormaDePago(FormaDePago)\0"
    "limpiarListaFormaDePago()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarFormaDePago(QString,QString)\0"
    "QString\0retornaDescripcionFormaDePago(QString)\0"
};

void ModuloFormasDePago::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloFormasDePago *_t = static_cast<ModuloFormasDePago *>(_o);
        switch (_id) {
        case 0: _t->agregarFormaDePago((*reinterpret_cast< const FormaDePago(*)>(_a[1]))); break;
        case 1: _t->limpiarListaFormaDePago(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarFormaDePago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionFormaDePago((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloFormasDePago::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloFormasDePago::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloFormasDePago,
      qt_meta_data_ModuloFormasDePago, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloFormasDePago::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloFormasDePago::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloFormasDePago::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloFormasDePago))
        return static_cast<void*>(const_cast< ModuloFormasDePago*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloFormasDePago::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
