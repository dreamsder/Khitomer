/****************************************************************************
** Meta object code from reading C++ file 'modulolistasprecios.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulolistasprecios.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulolistasprecios.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloListasPrecios[] = {

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
      34,   21,   20,   20, 0x02,
      64,   20,   20,   20, 0x02,
      95,   88,   84,   20, 0x02,
     117,   20,   84,   20, 0x22,
     148,  137,  128,   20, 0x02,
     176,  170,  128,   20, 0x22,
     196,  194,   20,   20, 0x02,
     239,  232,   84,   20, 0x02,
     317,   20,   84,   20, 0x02,
     359,   20,  354,   20, 0x02,
     397,   20,  389,   20, 0x02,
     439,  436,  389,   20, 0x02,
     492,  194,  354,   20, 0x02,
     537,  436,  354,   20, 0x02,
     589,  194,   20,   20, 0x02,
     632,  436,  389,   20, 0x02,
     673,   20,  389,   20, 0x02,
     712,   20,  389,   20, 0x02,
     756,  436,  354,   20, 0x02,
     818,  814,  354,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloListasPrecios[] = {
    "ModuloListasPrecios\0\0ListasPrecio\0"
    "addListasPrecio(ListasPrecio)\0"
    "clearListasPrecio()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarListasPrecio(QString,QString)\0"
    ",,,,,,\0"
    "insertarListasPrecio(QString,QString,QString,QString,QString,QString,Q"
    "String)\0"
    "ultimoRegistroDeListasPrecioEnBase()\0"
    "bool\0eliminarListasPrecio(QString)\0"
    "QString\0retornaDescripcionListaPrecio(QString)\0"
    ",,\0retornaListaPrecioDeCliente(QString,QString,QString)\0"
    "eliminaListaPrecioDeCliente(QString,QString)\0"
    "insertarListaPrecioCliente(QString,QString,QString)\0"
    "buscarListasPrecioCliente(QString,QString)\0"
    "retornarListaPrecio(int,QString,QString)\0"
    "retornaCodigoListaPrecioPorIndice(int)\0"
    "retornaDescripcionListaPrecioPorIndice(int)\0"
    "retornaSiClienteTieneListaPrecio(QString,QString,QString)\0"
    ",,,\0emitirListaPrecioDuplex(QString,QString,QString,int)\0"
};

void ModuloListasPrecios::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloListasPrecios *_t = static_cast<ModuloListasPrecios *>(_o);
        switch (_id) {
        case 0: _t->addListasPrecio((*reinterpret_cast< const ListasPrecio(*)>(_a[1]))); break;
        case 1: _t->clearListasPrecio(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarListasPrecio((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { int _r = _t->insertarListasPrecio((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->ultimoRegistroDeListasPrecioEnBase();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarListasPrecio((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaDescripcionListaPrecio((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaListaPrecioDeCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->eliminaListaPrecioDeCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->insertarListaPrecioCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: _t->buscarListasPrecioCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: { QString _r = _t->retornarListaPrecio((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->retornaCodigoListaPrecioPorIndice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { QString _r = _t->retornaDescripcionListaPrecioPorIndice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->retornaSiClienteTieneListaPrecio((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->emitirListaPrecioDuplex((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloListasPrecios::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloListasPrecios::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloListasPrecios,
      qt_meta_data_ModuloListasPrecios, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloListasPrecios::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloListasPrecios::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloListasPrecios::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloListasPrecios))
        return static_cast<void*>(const_cast< ModuloListasPrecios*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloListasPrecios::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
