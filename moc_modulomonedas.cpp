/****************************************************************************
** Meta object code from reading C++ file 'modulomonedas.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulomonedas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulomonedas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloMonedas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x02,
      47,   14,   14,   14, 0x02,
      80,   73,   69,   14, 0x02,
     102,   14,   69,   14, 0x22,
     133,  122,  113,   14, 0x02,
     161,  155,  113,   14, 0x22,
     181,  179,   14,   14, 0x02,
     220,  212,   69,   14, 0x02,
     306,   14,  301,   14, 0x02,
     339,   14,  331,   14, 0x02,
     373,   14,  331,   14, 0x02,
     403,   14,  331,   14, 0x02,
     439,   14,  432,   14, 0x02,
     472,   14,  331,   14, 0x02,
     505,  179,   69,   14, 0x02,
     543,   14,   69,   14, 0x02,
     584,  568,  331,   14, 0x02,
     632,  625,  331,   14, 0x02,
     666,  625,  331,   14, 0x02,
     705,  625,  331,   14, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloMonedas[] = {
    "ModuloMonedas\0\0Monedas\0agregarMonedas(Monedas)\0"
    "limpiarListaMonedas()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarMonedas(QString,QString)\0,,,,,,,\0"
    "insertarMonedas(QString,QString,QString,QString,QString,QString,QStrin"
    "g,QString)\0"
    "bool\0eliminarMonedas(QString)\0QString\0"
    "retornaDescripcionMoneda(QString)\0"
    "retornaSimboloMoneda(QString)\0"
    "retornaCodigoMoneda(QString)\0double\0"
    "retornaCotizacionMoneda(QString)\0"
    "retornaMonedaReferenciaSistema()\0"
    "actualizarCotizacion(QString,QString)\0"
    "ultimoRegistroDeMoneda()\0_codigoArticulo\0"
    "retornaSimboloMonedaPorArticulo(QString)\0"
    "indice\0retornaCodigoMonedaPorIndice(int)\0"
    "retornaDescripcionMonedaPorIndice(int)\0"
    "retornaSimboloMonedaPorIndice(int)\0"
};

void ModuloMonedas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloMonedas *_t = static_cast<ModuloMonedas *>(_o);
        switch (_id) {
        case 0: _t->agregarMonedas((*reinterpret_cast< const Monedas(*)>(_a[1]))); break;
        case 1: _t->limpiarListaMonedas(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarMonedas((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { int _r = _t->insertarMonedas((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->eliminarMonedas((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->retornaDescripcionMoneda((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaSimboloMoneda((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaCodigoMoneda((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { double _r = _t->retornaCotizacionMoneda((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 13: { QString _r = _t->retornaMonedaReferenciaSistema();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: { int _r = _t->actualizarCotizacion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = _t->ultimoRegistroDeMoneda();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->retornaSimboloMonedaPorArticulo((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { QString _r = _t->retornaCodigoMonedaPorIndice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 18: { QString _r = _t->retornaDescripcionMonedaPorIndice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 19: { QString _r = _t->retornaSimboloMonedaPorIndice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloMonedas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloMonedas::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloMonedas,
      qt_meta_data_ModuloMonedas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloMonedas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloMonedas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloMonedas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloMonedas))
        return static_cast<void*>(const_cast< ModuloMonedas*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloMonedas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
