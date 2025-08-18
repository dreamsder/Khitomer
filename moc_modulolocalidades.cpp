/****************************************************************************
** Meta object code from reading C++ file 'modulolocalidades.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulolocalidades.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulolocalidades.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloLocalidades[] = {

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
      29,   19,   18,   18, 0x02,
      57,   18,   18,   18, 0x02,
      94,   87,   83,   18, 0x02,
     116,   18,   83,   18, 0x22,
     147,  136,  127,   18, 0x02,
     175,  169,  127,   18, 0x22,
     195,  193,   18,   18, 0x02,
     241,  238,  230,   18, 0x02,
     294,  193,  230,   18, 0x02,
     344,  340,   83,   18, 0x02,
     400,  238,  395,   18, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloLocalidades[] = {
    "ModuloLocalidades\0\0Localidad\0"
    "agregarLocalidad(Localidad)\0"
    "limpiarListaLocalidades()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarLocalidades(QString,QString)\0"
    "QString\0,,\0"
    "retornaDescripcionLocalidad(QString,QString,QString)\0"
    "retornaUltimoCodigoLocalidad(QString,QString)\0"
    ",,,\0insertarLocalidad(QString,QString,QString,QString)\0"
    "bool\0eliminarLocalidad(QString,QString,QString)\0"
};

void ModuloLocalidades::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloLocalidades *_t = static_cast<ModuloLocalidades *>(_o);
        switch (_id) {
        case 0: _t->agregarLocalidad((*reinterpret_cast< const Localidad(*)>(_a[1]))); break;
        case 1: _t->limpiarListaLocalidades(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarLocalidades((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionLocalidad((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaUltimoCodigoLocalidad((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->insertarLocalidad((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->eliminarLocalidad((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloLocalidades::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloLocalidades::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloLocalidades,
      qt_meta_data_ModuloLocalidades, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloLocalidades::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloLocalidades::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloLocalidades::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloLocalidades))
        return static_cast<void*>(const_cast< ModuloLocalidades*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloLocalidades::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
