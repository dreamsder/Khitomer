/****************************************************************************
** Meta object code from reading C++ file 'modulo_cfe_parametrosgenerales.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CFE/modulo_cfe_parametrosgenerales.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulo_cfe_parametrosgenerales.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Modulo_CFE_ParametrosGenerales[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      56,   32,   31,   31, 0x02,
      89,   31,   31,   31, 0x02,
     110,  103,   99,   31, 0x02,
     132,   31,   99,   31, 0x22,
     163,  152,  143,   31, 0x02,
     191,  185,  143,   31, 0x22,
     211,  209,   31,   31, 0x02,
     235,   31,   31,   31, 0x02,
     252,   31,  244,   31, 0x02,
     279,   31,  274,   31, 0x02,
     300,   31,  274,   31, 0x02,
     322,  209,  274,   31, 0x02,
     366,  209,  274,   31, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Modulo_CFE_ParametrosGenerales[] = {
    "Modulo_CFE_ParametrosGenerales\0\0"
    "CFE_ParametrosGenerales\0"
    "agregar(CFE_ParametrosGenerales)\0"
    "limpiar()\0int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0QVariant\0index,role\0"
    "data(QModelIndex,int)\0index\0"
    "data(QModelIndex)\0,\0buscar(QString,QString)\0"
    "cargar()\0QString\0retornaValor(QString)\0"
    "bool\0cargarClavePublica()\0"
    "cargarLogoImpresora()\0"
    "actualizarDatoParametroCFE(QString,QString)\0"
    "actualizarDatoParametroCFEImagen(QString,QString)\0"
};

void Modulo_CFE_ParametrosGenerales::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Modulo_CFE_ParametrosGenerales *_t = static_cast<Modulo_CFE_ParametrosGenerales *>(_o);
        switch (_id) {
        case 0: _t->agregar((*reinterpret_cast< const CFE_ParametrosGenerales(*)>(_a[1]))); break;
        case 1: _t->limpiar(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscar((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->cargar(); break;
        case 8: { QString _r = _t->retornaValor((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->cargarClavePublica();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->cargarLogoImpresora();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->actualizarDatoParametroCFE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->actualizarDatoParametroCFEImagen((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Modulo_CFE_ParametrosGenerales::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Modulo_CFE_ParametrosGenerales::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_Modulo_CFE_ParametrosGenerales,
      qt_meta_data_Modulo_CFE_ParametrosGenerales, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Modulo_CFE_ParametrosGenerales::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Modulo_CFE_ParametrosGenerales::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Modulo_CFE_ParametrosGenerales::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Modulo_CFE_ParametrosGenerales))
        return static_cast<void*>(const_cast< Modulo_CFE_ParametrosGenerales*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int Modulo_CFE_ParametrosGenerales::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
