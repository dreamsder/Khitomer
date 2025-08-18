/****************************************************************************
** Meta object code from reading C++ file 'moduloconfiguracion.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Utilidades/moduloconfiguracion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloconfiguracion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloConfiguracion[] = {

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
      35,   21,   20,   20, 0x02,
      71,   20,   20,   20, 0x02,
     110,  103,   99,   20, 0x02,
     132,   20,   99,   20, 0x22,
     163,  152,  143,   20, 0x02,
     191,  185,  143,   20, 0x22,
     211,  209,   20,   20, 0x02,
     248,   20,   20,   20, 0x02,
     278,   20,  270,   20, 0x02,
     339,  318,  313,   20, 0x02,
     382,  318,  270,   20, 0x02,
     428,   20,  270,   20, 0x02,
     461,   20,  313,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloConfiguracion[] = {
    "ModuloConfiguracion\0\0Configuracion\0"
    "agregarConfiguracion(Configuracion)\0"
    "limpiarListaConfiguracion()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarConfiguracion(QString,QString)\0"
    "cargarConfiguracion()\0QString\0"
    "retornaValorConfiguracion(QString)\0"
    "bool\0_codigoConfiguracion\0"
    "retornaValorConfiguracionBooleano(QString)\0"
    "retornaValorConfiguracionValorString(QString)\0"
    "retornaCantidadDecimalesString()\0"
    "retornaModoAvisoDocumentosNuevoVisible()\0"
};

void ModuloConfiguracion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloConfiguracion *_t = static_cast<ModuloConfiguracion *>(_o);
        switch (_id) {
        case 0: _t->agregarConfiguracion((*reinterpret_cast< const Configuracion(*)>(_a[1]))); break;
        case 1: _t->limpiarListaConfiguracion(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarConfiguracion((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->cargarConfiguracion(); break;
        case 8: { QString _r = _t->retornaValorConfiguracion((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->retornaValorConfiguracionBooleano((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaValorConfiguracionValorString((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaCantidadDecimalesString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->retornaModoAvisoDocumentosNuevoVisible();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloConfiguracion::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloConfiguracion::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloConfiguracion,
      qt_meta_data_ModuloConfiguracion, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloConfiguracion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloConfiguracion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloConfiguracion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloConfiguracion))
        return static_cast<void*>(const_cast< ModuloConfiguracion*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloConfiguracion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
