/****************************************************************************
** Meta object code from reading C++ file 'modulosubrubros.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulosubrubros.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulosubrubros.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloSubRubros[] = {

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
      27,   17,   16,   16, 0x02,
      55,   16,   16,   16, 0x02,
      90,   83,   79,   16, 0x02,
     112,   16,   79,   16, 0x22,
     143,  132,  123,   16, 0x02,
     171,  165,  123,   16, 0x22,
     191,  189,   16,   16, 0x02,
     232,   16,  224,   16, 0x02,
     268,   16,   79,   16, 0x02,
     300,   16,  295,   16, 0x02,
     329,  326,   79,   16, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloSubRubros[] = {
    "ModuloSubRubros\0\0SubRubros\0"
    "agregarSubRubros(SubRubros)\0"
    "limpiarListaSubRubros()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarSubRubros(QString,QString)\0"
    "QString\0retornaDescripcionSubRubro(QString)\0"
    "ultimoRegistroDeSubRubro()\0bool\0"
    "eliminarSubRubro(QString)\0,,\0"
    "insertarSubRubro(QString,QString,QString)\0"
};

void ModuloSubRubros::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloSubRubros *_t = static_cast<ModuloSubRubros *>(_o);
        switch (_id) {
        case 0: _t->agregarSubRubros((*reinterpret_cast< const SubRubros(*)>(_a[1]))); break;
        case 1: _t->limpiarListaSubRubros(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarSubRubros((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionSubRubro((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->ultimoRegistroDeSubRubro();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarSubRubro((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->insertarSubRubro((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloSubRubros::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloSubRubros::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloSubRubros,
      qt_meta_data_ModuloSubRubros, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloSubRubros::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloSubRubros::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloSubRubros::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloSubRubros))
        return static_cast<void*>(const_cast< ModuloSubRubros*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloSubRubros::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
