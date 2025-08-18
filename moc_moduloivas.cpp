/****************************************************************************
** Meta object code from reading C++ file 'moduloivas.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloivas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloivas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloIvas[] = {

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
      17,   12,   11,   11, 0x02,
      34,   11,   11,   11, 0x02,
      64,   57,   53,   11, 0x02,
      86,   11,   53,   11, 0x22,
     117,  106,   97,   11, 0x02,
     145,  139,   97,   11, 0x22,
     165,  163,   11,   11, 0x02,
     201,   11,  193,   11, 0x02,
     239,   11,  232,   11, 0x02,
     275,   11,  232,   11, 0x02,
     317,   11,  193,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloIvas[] = {
    "ModuloIvas\0\0Ivas\0agregarIva(Ivas)\0"
    "limpiarListaIvas()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarIvas(QString,QString)\0QString\0"
    "retornaDescripcionIva(QString)\0double\0"
    "retornaFactorMultiplicador(QString)\0"
    "retornaFactorMultiplicadorIVAPorDefecto()\0"
    "retornaCodigoIva(QString)\0"
};

void ModuloIvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloIvas *_t = static_cast<ModuloIvas *>(_o);
        switch (_id) {
        case 0: _t->agregarIva((*reinterpret_cast< const Ivas(*)>(_a[1]))); break;
        case 1: _t->limpiarListaIvas(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarIvas((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaDescripcionIva((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { double _r = _t->retornaFactorMultiplicador((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 9: { double _r = _t->retornaFactorMultiplicadorIVAPorDefecto();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaCodigoIva((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloIvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloIvas::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloIvas,
      qt_meta_data_ModuloIvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloIvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloIvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloIvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloIvas))
        return static_cast<void*>(const_cast< ModuloIvas*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloIvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
