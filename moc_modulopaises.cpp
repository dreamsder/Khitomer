/****************************************************************************
** Meta object code from reading C++ file 'modulopaises.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulopaises.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulopaises.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloPaises[] = {

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
      19,   14,   13,   13, 0x02,
      37,   13,   13,   13, 0x02,
      69,   62,   58,   13, 0x02,
      91,   13,   58,   13, 0x22,
     122,  111,  102,   13, 0x02,
     150,  144,  102,   13, 0x22,
     171,  168,   13,   13, 0x02,
     217,   13,  209,   13, 0x02,
     248,   13,  243,   13, 0x02,
     272,  270,   58,   13, 0x02,
     302,   13,  209,   13, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloPaises[] = {
    "ModuloPaises\0\0Pais\0agregarPais(Pais)\0"
    "limpiarListaPaises()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,,\0"
    "buscarPaises(QString,QString,QString)\0"
    "QString\0retornaUltimoCodigoPais()\0"
    "bool\0eliminarPais(QString)\0,\0"
    "insertarPais(QString,QString)\0"
    "retornaDescripcionPais(QString)\0"
};

void ModuloPaises::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloPaises *_t = static_cast<ModuloPaises *>(_o);
        switch (_id) {
        case 0: _t->agregarPais((*reinterpret_cast< const Pais(*)>(_a[1]))); break;
        case 1: _t->limpiarListaPaises(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarPaises((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: { QString _r = _t->retornaUltimoCodigoPais();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->eliminarPais((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->insertarPais((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaDescripcionPais((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloPaises::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloPaises::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloPaises,
      qt_meta_data_ModuloPaises, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloPaises::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloPaises::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloPaises::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloPaises))
        return static_cast<void*>(const_cast< ModuloPaises*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloPaises::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
