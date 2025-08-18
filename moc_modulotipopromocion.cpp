/****************************************************************************
** Meta object code from reading C++ file 'modulotipopromocion.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulotipopromocion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulotipopromocion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloTipoPromocion[] = {

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
      35,   21,   20,   20, 0x02,
      71,   20,   20,   20, 0x02,
     105,   98,   94,   20, 0x02,
     127,   20,   94,   20, 0x22,
     158,  147,  138,   20, 0x02,
     186,  180,  138,   20, 0x22,
     204,   20,   20,   20, 0x02,
     243,  241,  233,   20, 0x02,
     269,   20,  233,   20, 0x02,
     303,   20,  298,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloTipoPromocion[] = {
    "ModuloTipoPromocion\0\0TipoPromocion\0"
    "agregarTipoPromocion(TipoPromocion)\0"
    "limpiarTipoPromocion()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0"
    "buscarTipoPromocion(QString)\0QString\0"
    ",\0retornaValor(int,QString)\0"
    "retornaUltimoTipoPromocion()\0bool\0"
    "eliminarTipoPromocion(QString)\0"
};

void ModuloTipoPromocion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloTipoPromocion *_t = static_cast<ModuloTipoPromocion *>(_o);
        switch (_id) {
        case 0: _t->agregarTipoPromocion((*reinterpret_cast< const TipoPromocion(*)>(_a[1]))); break;
        case 1: _t->limpiarTipoPromocion(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarTipoPromocion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { QString _r = _t->retornaValor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaUltimoTipoPromocion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarTipoPromocion((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloTipoPromocion::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloTipoPromocion::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloTipoPromocion,
      qt_meta_data_ModuloTipoPromocion, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloTipoPromocion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloTipoPromocion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloTipoPromocion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloTipoPromocion))
        return static_cast<void*>(const_cast< ModuloTipoPromocion*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloTipoPromocion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
