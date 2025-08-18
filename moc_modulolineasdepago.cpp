/****************************************************************************
** Meta object code from reading C++ file 'modulolineasdepago.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulolineasdepago.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulolineasdepago.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloLineasDePago[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      33,   20,   19,   19, 0x02,
      66,   19,   19,   19, 0x02,
     104,   97,   93,   19, 0x02,
     126,   19,   93,   19, 0x22,
     157,  146,  137,   19, 0x02,
     185,  179,  137,   19, 0x22,
     205,  203,   19,   19, 0x02,
     257,  203,   19,   19, 0x02,
     336,  331,  326,   19, 0x02,
     413,  331,  326,   19, 0x02,
     494,  490,  326,   19, 0x02,
     566,   19,  558,   19, 0x02,
     594,   19,  558,   19, 0x02,
     626,   19,  558,   19, 0x02,
     653,   19,  558,   19, 0x02,
     677,   19,  558,   19, 0x02,
     705,   19,  558,   19, 0x02,
     733,   19,  558,   19, 0x02,
     757,   19,  558,   19, 0x02,
     776,   19,  558,   19, 0x02,
     800,   19,  558,   19, 0x02,
     833,   19,  558,   19, 0x02,
     858,   19,  558,   19, 0x02,
     885,   19,  558,   19, 0x02,
     910,   19,  558,   19, 0x02,
     939,   19,  558,   19, 0x02,
     963,   19,  558,   19, 0x02,
     996,   19,  558,   19, 0x02,
    1051, 1034,  558,   19, 0x02,
    1116, 1098,  558,   19, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloLineasDePago[] = {
    "ModuloLineasDePago\0\0LineasDePago\0"
    "agregarLineaDePago(LineasDePago)\0"
    "limpiarListaLineasDePago()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarLineasDePagoChequesDiferidos(QString,QString)\0"
    "buscarLineasDePagoTarjetasDeCreditoPendientesDePago(QString,QString)\0"
    "bool\0,,,,\0"
    "actualizarLineaDePagoChequeDiferido(QString,QString,QString,QString,QS"
    "tring)\0"
    "actualizarLineaDePagoTarjetaCredito(QString,QString,QString,QString,QS"
    "tring)\0"
    ",,,\0verificaMedioPagoEstaUtilizado(QString,QString,QString,QString)\0"
    "QString\0retornacodigoDocumento(int)\0"
    "retornacodigoTipoDocumento(int)\0"
    "retornaSerieDocumento(int)\0"
    "retornanumeroLinea(int)\0"
    "retornacodigoMedioPago(int)\0"
    "retornamonedaMedioPago(int)\0"
    "retornaimportePago(int)\0retornacuotas(int)\0"
    "retornacodigoBanco(int)\0"
    "retornacodigoTarjetaCredito(int)\0"
    "retornanumeroCheque(int)\0"
    "retornatarjetaCobrada(int)\0"
    "retornamontoCobrado(int)\0"
    "retornacodigoTipoCheque(int)\0"
    "retornafechaCheque(int)\0"
    "retornanumeroCuentaBancaria(int)\0"
    "retornacodigoBancoCuentaBancaria(int)\0"
    ",,serieDocumento\0"
    "retornaRazonDeCliente(QString,QString,QString)\0"
    ",,_serieDocumento\0"
    "retornaFechaDocumento(QString,QString,QString)\0"
};

void ModuloLineasDePago::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloLineasDePago *_t = static_cast<ModuloLineasDePago *>(_o);
        switch (_id) {
        case 0: _t->agregarLineaDePago((*reinterpret_cast< const LineasDePago(*)>(_a[1]))); break;
        case 1: _t->limpiarListaLineasDePago(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarLineasDePagoChequesDiferidos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->buscarLineasDePagoTarjetasDeCreditoPendientesDePago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: { bool _r = _t->actualizarLineaDePagoChequeDiferido((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->actualizarLineaDePagoTarjetaCredito((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->verificaMedioPagoEstaUtilizado((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornacodigoDocumento((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->retornacodigoTipoDocumento((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: { QString _r = _t->retornaSerieDocumento((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->retornanumeroLinea((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { QString _r = _t->retornacodigoMedioPago((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->retornamonedaMedioPago((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { QString _r = _t->retornaimportePago((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 18: { QString _r = _t->retornacuotas((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 19: { QString _r = _t->retornacodigoBanco((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: { QString _r = _t->retornacodigoTarjetaCredito((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 21: { QString _r = _t->retornanumeroCheque((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: { QString _r = _t->retornatarjetaCobrada((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 23: { QString _r = _t->retornamontoCobrado((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 24: { QString _r = _t->retornacodigoTipoCheque((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 25: { QString _r = _t->retornafechaCheque((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 26: { QString _r = _t->retornanumeroCuentaBancaria((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 27: { QString _r = _t->retornacodigoBancoCuentaBancaria((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 28: { QString _r = _t->retornaRazonDeCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 29: { QString _r = _t->retornaFechaDocumento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloLineasDePago::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloLineasDePago::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloLineasDePago,
      qt_meta_data_ModuloLineasDePago, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloLineasDePago::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloLineasDePago::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloLineasDePago::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloLineasDePago))
        return static_cast<void*>(const_cast< ModuloLineasDePago*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloLineasDePago::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
