/****************************************************************************
** Meta object code from reading C++ file 'modulorubros.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulorubros.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulorubros.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloRubros[] = {

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
      21,   14,   13,   13, 0x02,
      42,   13,   13,   13, 0x02,
      74,   67,   63,   13, 0x02,
      96,   13,   63,   13, 0x22,
     127,  116,  107,   13, 0x02,
     155,  149,  107,   13, 0x22,
     175,  173,   13,   13, 0x02,
     205,   13,   63,   13, 0x02,
     247,   13,  239,   13, 0x02,
     275,  173,   63,   13, 0x02,
     311,   13,  306,   13, 0x02,
     334,   13,   63,   13, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloRubros[] = {
    "ModuloRubros\0\0Rubros\0agregarRubro(Rubros)\0"
    "limpiarListaRubros()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarRubros(QString,QString)\0"
    "retornaCantidadSubRubros(QString)\0"
    "QString\0retornaNombreRubro(QString)\0"
    "insertarRubro(QString,QString)\0bool\0"
    "eliminarRubro(QString)\0ultimoRegistroDeRubro()\0"
};

void ModuloRubros::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloRubros *_t = static_cast<ModuloRubros *>(_o);
        switch (_id) {
        case 0: _t->agregarRubro((*reinterpret_cast< const Rubros(*)>(_a[1]))); break;
        case 1: _t->limpiarListaRubros(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarRubros((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { int _r = _t->retornaCantidadSubRubros((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaNombreRubro((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->insertarRubro((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->eliminarRubro((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->ultimoRegistroDeRubro();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloRubros::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloRubros::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloRubros,
      qt_meta_data_ModuloRubros, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloRubros::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloRubros::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloRubros::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloRubros))
        return static_cast<void*>(const_cast< ModuloRubros*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloRubros::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
