/****************************************************************************
** Meta object code from reading C++ file 'modulomediosdepago.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulomediosdepago.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulomediosdepago.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloMediosDePago[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
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
     247,   19,  242,   19, 0x02,
     270,   19,  242,   19, 0x02,
     292,   19,  242,   19, 0x02,
     321,   19,  242,   19, 0x02,
     360,   19,  352,   19, 0x02,
     399,   19,  352,   19, 0x02,
     466,  433,  242,   19, 0x02,
     638,  635,  242,   19, 0x02,
     715,  697,   94,   19, 0x02,
     792,  773,  352,   19, 0x02,
     846,  773,  839,   19, 0x02,
     898,  773,  352,   19, 0x02,
     954,  773,  352,   19, 0x02,
    1010,  773,  352,   19, 0x02,
    1071,  773,  352,   19, 0x02,
    1123,  773,  352,   19, 0x02,
    1176,  773,  352,   19, 0x02,
    1228,  773,  352,   19, 0x02,
    1279,  773,  352,   19, 0x02,
    1334,  773,  352,   19, 0x02,
    1394,  773,  352,   19, 0x02,
    1456,  773,  242,   19, 0x02,
    1513,  773,  352,   19, 0x02,
    1579,  773,  352,   19, 0x02,
    1707, 1646,  352,   19, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloMediosDePago[] = {
    "ModuloMediosDePago\0\0MediosDePago\0"
    "agregarMediosDePago(MediosDePago)\0"
    "limpiarListaMediosDePago()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarMediosDePago(QString,QString)\0"
    "bool\0utilizaCuotas(QString)\0"
    "utilizaBanco(QString)\0"
    "utilizaNumeroCheque(QString)\0"
    "utilizaCuentaBancaria(QString)\0QString\0"
    "retornaDescripcionMedioDePago(QString)\0"
    "retornaMonedaMedioDePago(QString)\0"
    ",,,,,,,,,,,,,,,,,_serieDocumento\0"
    "guardarLineaMedioDePago(QString,QString,QString,QString,QString,QStrin"
    "g,QString,QString,QString,QString,QString,QString,QString,QString,QStr"
    "ing,QString,QString,QString)\0"
    ",,\0eliminarLineaMedioDePagoDocumento(QString,QString,QString)\0"
    ",,_serieDocumento\0"
    "retornaCantidadLineasMedioDePago(QString,QString,QString)\0"
    ",,,_serieDocumento\0"
    "retornoCuotas(QString,QString,QString,QString)\0"
    "double\0retornoImportePago(QString,QString,QString,QString)\0"
    "retornoMonedaMedioPago(QString,QString,QString,QString)\0"
    "retornoCodigoMedioPago(QString,QString,QString,QString)\0"
    "retornoCodigoTarjetaCredito(QString,QString,QString,QString)\0"
    "retornoCodigoBanco(QString,QString,QString,QString)\0"
    "retornoNumeroCheque(QString,QString,QString,QString)\0"
    "retornoFechaCheque(QString,QString,QString,QString)\0"
    "retornoTipoCheque(QString,QString,QString,QString)\0"
    "retornoCuentaBancaria(QString,QString,QString,QString)\0"
    "retornoBancoCuentaBancaria(QString,QString,QString,QString)\0"
    "retornoCodigoDocumentoCheque(QString,QString,QString,QString)\0"
    "retornoEsDiferidoCheque(QString,QString,QString,QString)\0"
    "retornoCodigoTipoDocumentoCheque(QString,QString,QString,QString)\0"
    "retornoNumeroLineaDocumentoCheque(QString,QString,QString,QString)\0"
    "_codigoDocumento,_codigoTipoDocumento,_linea,_serieDocumento\0"
    "retornoSerieDocumentoCheque(QString,QString,QString,QString)\0"
};

void ModuloMediosDePago::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloMediosDePago *_t = static_cast<ModuloMediosDePago *>(_o);
        switch (_id) {
        case 0: _t->agregarMediosDePago((*reinterpret_cast< const MediosDePago(*)>(_a[1]))); break;
        case 1: _t->limpiarListaMediosDePago(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarMediosDePago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { bool _r = _t->utilizaCuotas((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->utilizaBanco((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->utilizaNumeroCheque((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->utilizaCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaDescripcionMedioDePago((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->retornaMonedaMedioDePago((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->guardarLineaMedioDePago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9])),(*reinterpret_cast< QString(*)>(_a[10])),(*reinterpret_cast< QString(*)>(_a[11])),(*reinterpret_cast< QString(*)>(_a[12])),(*reinterpret_cast< QString(*)>(_a[13])),(*reinterpret_cast< QString(*)>(_a[14])),(*reinterpret_cast< QString(*)>(_a[15])),(*reinterpret_cast< QString(*)>(_a[16])),(*reinterpret_cast< QString(*)>(_a[17])),(*reinterpret_cast< QString(*)>(_a[18])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->eliminarLineaMedioDePagoDocumento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { int _r = _t->retornaCantidadLineasMedioDePago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->retornoCuotas((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { double _r = _t->retornoImportePago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 18: { QString _r = _t->retornoMonedaMedioPago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 19: { QString _r = _t->retornoCodigoMedioPago((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: { QString _r = _t->retornoCodigoTarjetaCredito((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 21: { QString _r = _t->retornoCodigoBanco((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: { QString _r = _t->retornoNumeroCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 23: { QString _r = _t->retornoFechaCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 24: { QString _r = _t->retornoTipoCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 25: { QString _r = _t->retornoCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 26: { QString _r = _t->retornoBancoCuentaBancaria((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 27: { QString _r = _t->retornoCodigoDocumentoCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 28: { bool _r = _t->retornoEsDiferidoCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 29: { QString _r = _t->retornoCodigoTipoDocumentoCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 30: { QString _r = _t->retornoNumeroLineaDocumentoCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 31: { QString _r = _t->retornoSerieDocumentoCheque((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloMediosDePago::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloMediosDePago::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloMediosDePago,
      qt_meta_data_ModuloMediosDePago, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloMediosDePago::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloMediosDePago::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloMediosDePago::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloMediosDePago))
        return static_cast<void*>(const_cast< ModuloMediosDePago*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloMediosDePago::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
