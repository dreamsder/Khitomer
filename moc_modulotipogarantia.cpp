/****************************************************************************
** Meta object code from reading C++ file 'modulotipogarantia.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulotipogarantia.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulotipogarantia.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloTipoGarantia[] = {

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
      33,   20,   19,   19, 0x02,
      67,   19,   19,   19, 0x02,
     105,   98,   94,   19, 0x02,
     127,   19,   94,   19, 0x22,
     158,  147,  138,   19, 0x02,
     186,  180,  138,   19, 0x22,
     206,  204,   19,   19, 0x02,
     250,   19,  242,   19, 0x02,
     290,   19,  242,   19, 0x02,
     325,  317,  312,   19, 0x02,
     343,  204,   94,   19, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloTipoGarantia[] = {
    "ModuloTipoGarantia\0\0TipoGarantia\0"
    "agregarTipoGarantia(TipoGarantia)\0"
    "limpiarListaTipoGarantia()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarTipoGarantia(QString,QString)\0"
    "QString\0retornaDescripcionTipoGarantia(QString)\0"
    "retornaUltimoCodigo()\0bool\0_codigo\0"
    "eliminar(QString)\0"
    "insertarTipoGarantia(QString,QString)\0"
};

void ModuloTipoGarantia::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloTipoGarantia *_t = static_cast<ModuloTipoGarantia *>(_o);
        switch (_id) {
        case 0: _t->agregarTipoGarantia((*reinterpret_cast< const TipoGarantia(*)>(_a[1]))); break;
        case 1: _t->limpiarListaTipoGarantia(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarTipoGarantia((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionTipoGarantia((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaUltimoCodigo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminar((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->insertarTipoGarantia((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloTipoGarantia::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloTipoGarantia::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloTipoGarantia,
      qt_meta_data_ModuloTipoGarantia, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloTipoGarantia::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloTipoGarantia::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloTipoGarantia::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloTipoGarantia))
        return static_cast<void*>(const_cast< ModuloTipoGarantia*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloTipoGarantia::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
