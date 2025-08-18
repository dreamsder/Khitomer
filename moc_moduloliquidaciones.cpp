/****************************************************************************
** Meta object code from reading C++ file 'moduloliquidaciones.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloliquidaciones.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloliquidaciones.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloLiquidaciones[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      33,   21,   20,   20, 0x02,
      61,   20,   20,   20, 0x02,
      93,   86,   82,   20, 0x02,
     115,   20,   82,   20, 0x22,
     146,  135,  126,   20, 0x02,
     174,  168,  126,   20, 0x22,
     194,  192,   20,   20, 0x02,
     232,  229,   82,   20, 0x02,
     277,   20,   82,   20, 0x02,
     325,  192,  320,   20, 0x02,
     370,   20,  362,   20, 0x02,
     429,  192,  362,   20, 0x02,
     486,   20,  362,   20, 0x02,
     526,   20,  362,   20, 0x02,
     574,   20,  362,   20, 0x02,
     618,  229,  362,   20, 0x02,
     686,  229,  362,   20, 0x02,
     761,  192,  320,   20, 0x02,
     796,  192,  320,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloLiquidaciones[] = {
    "ModuloLiquidaciones\0\0Liquidacion\0"
    "addLiquidacion(Liquidacion)\0"
    "clearLiquidaciones()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarLiquidacion(QString,QString)\0"
    ",,\0insertarLiquidacion(QString,QString,QString)\0"
    "ultimoRegistroDeLiquidacionEnBase(QString)\0"
    "bool\0eliminarLiquidacion(QString,QString)\0"
    "QString\0"
    "retornaDescripcionLiquidacionDeVendedorPorDefault(QString)\0"
    "retornaDescripcionLiquidacionDeVendedor(QString,QString)\0"
    "retornaNumeroPrimeraLiquidacionActiva()\0"
    "retornaCodigoVendedorPrimeraLiquidacionActiva()\0"
    "retornaNumeroLiquidacionDeVendedor(QString)\0"
    "retornaValorTotalDocumentosEnLiquidaciones(QString,QString,QString)\0"
    "retornaCantidadDocumentosEnLiquidacionSegunEstado(QString,QString,QStr"
    "ing)\0"
    "cerrarLiquidacion(QString,QString)\0"
    "liquidacionActiva(QString,QString)\0"
};

void ModuloLiquidaciones::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloLiquidaciones *_t = static_cast<ModuloLiquidaciones *>(_o);
        switch (_id) {
        case 0: _t->addLiquidacion((*reinterpret_cast< const Liquidacion(*)>(_a[1]))); break;
        case 1: _t->clearLiquidaciones(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarLiquidacion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { int _r = _t->insertarLiquidacion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->ultimoRegistroDeLiquidacionEnBase((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarLiquidacion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaDescripcionLiquidacionDeVendedorPorDefault((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaDescripcionLiquidacionDeVendedor((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->retornaNumeroPrimeraLiquidacionActiva();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: { QString _r = _t->retornaCodigoVendedorPrimeraLiquidacionActiva();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->retornaNumeroLiquidacionDeVendedor((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { QString _r = _t->retornaValorTotalDocumentosEnLiquidaciones((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->retornaCantidadDocumentosEnLiquidacionSegunEstado((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { bool _r = _t->cerrarLiquidacion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->liquidacionActiva((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloLiquidaciones::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloLiquidaciones::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloLiquidaciones,
      qt_meta_data_ModuloLiquidaciones, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloLiquidaciones::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloLiquidaciones::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloLiquidaciones::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloLiquidaciones))
        return static_cast<void*>(const_cast< ModuloLiquidaciones*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloLiquidaciones::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
