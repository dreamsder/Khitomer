/****************************************************************************
** Meta object code from reading C++ file 'modulopromociones.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulopromociones.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulopromociones.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloPromociones[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      31,   19,   18,   18, 0x02,
      63,   18,   18,   18, 0x02,
      95,   88,   84,   18, 0x02,
     117,   18,   84,   18, 0x22,
     148,  137,  128,   18, 0x02,
     176,  170,  128,   18, 0x22,
     194,   18,   18,   18, 0x02,
     231,  229,  221,   18, 0x02,
     257,   18,  221,   18, 0x02,
     289,   18,  284,   18, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloPromociones[] = {
    "ModuloPromociones\0\0Promociones\0"
    "agregarPromociones(Promociones)\0"
    "limpiarPromociones()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0"
    "buscarPromociones(QString)\0QString\0,\0"
    "retornaValor(int,QString)\0"
    "retornaUltimoPromociones()\0bool\0"
    "eliminarPromociones(QString)\0"
};

void ModuloPromociones::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloPromociones *_t = static_cast<ModuloPromociones *>(_o);
        switch (_id) {
        case 0: _t->agregarPromociones((*reinterpret_cast< const Promociones(*)>(_a[1]))); break;
        case 1: _t->limpiarPromociones(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarPromociones((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { QString _r = _t->retornaValor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaUltimoPromociones();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarPromociones((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloPromociones::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloPromociones::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloPromociones,
      qt_meta_data_ModuloPromociones, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloPromociones::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloPromociones::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloPromociones::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloPromociones))
        return static_cast<void*>(const_cast< ModuloPromociones*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloPromociones::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
