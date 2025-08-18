/****************************************************************************
** Meta object code from reading C++ file 'moduloclientes.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloclientes.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloclientes.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloClientes[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x02,
      44,   15,   15,   15, 0x02,
      71,   64,   60,   15, 0x02,
      93,   15,   60,   15, 0x22,
     124,  113,  104,   15, 0x02,
     152,  146,  104,   15, 0x22,
     172,  170,   15,   15, 0x02,
     213,   15,  203,   15, 0x02,
     252,   15,  203,   15, 0x02,
     356,  292,  284,   15, 0x02,
     618,  170,  613,   15, 0x02,
     651,  170,  284,   15, 0x02,
     696,  170,  613,   15, 0x02,
     763,  735,  613,   15, 0x02,
     846,  811,  284,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloClientes[] = {
    "ModuloClientes\0\0Cliente\0addCliente(Cliente)\0"
    "clearClientes()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarCliente(QString,QString)\0qlonglong\0"
    "ultimoRegistroDeClienteEnBase(QString)\0"
    "primerRegistroDeClienteEnBase()\0QString\0"
    ",,,,,,,,,,,,,,,,,,,,,,,,,,,_codigoTipoDocumentoDefault,,_email2\0"
    "insertarCliente(QString,QString,QString,QString,QString,QString,QStrin"
    "g,QString,QString,QString,QString,QString,QString,QString,QString,QStr"
    "ing,QString,QString,QString,QString,QString,QString,QString,QString,QS"
    "tring,QString,QString,QString,QString,QString)\0"
    "bool\0eliminarCliente(QString,QString)\0"
    "retornaDescripcionDeCliente(QString,QString)\0"
    "retornaSiEsClienteWeb(QString,QString)\0"
    "_codigoCliente,_tipoCliente\0"
    "retornaSiPermiteFacturaCredito(QString,QString)\0"
    "_codigoCliente,_tipoCliente,_campo\0"
    "retornaDatoGenericoCliente(QString,QString,QString)\0"
};

void ModuloClientes::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloClientes *_t = static_cast<ModuloClientes *>(_o);
        switch (_id) {
        case 0: _t->addCliente((*reinterpret_cast< const Cliente(*)>(_a[1]))); break;
        case 1: _t->clearClientes(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { qlonglong _r = _t->ultimoRegistroDeClienteEnBase((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qlonglong*>(_a[0]) = _r; }  break;
        case 8: { qlonglong _r = _t->primerRegistroDeClienteEnBase();
            if (_a[0]) *reinterpret_cast< qlonglong*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->insertarCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9])),(*reinterpret_cast< QString(*)>(_a[10])),(*reinterpret_cast< QString(*)>(_a[11])),(*reinterpret_cast< QString(*)>(_a[12])),(*reinterpret_cast< QString(*)>(_a[13])),(*reinterpret_cast< QString(*)>(_a[14])),(*reinterpret_cast< QString(*)>(_a[15])),(*reinterpret_cast< QString(*)>(_a[16])),(*reinterpret_cast< QString(*)>(_a[17])),(*reinterpret_cast< QString(*)>(_a[18])),(*reinterpret_cast< QString(*)>(_a[19])),(*reinterpret_cast< QString(*)>(_a[20])),(*reinterpret_cast< QString(*)>(_a[21])),(*reinterpret_cast< QString(*)>(_a[22])),(*reinterpret_cast< QString(*)>(_a[23])),(*reinterpret_cast< QString(*)>(_a[24])),(*reinterpret_cast< QString(*)>(_a[25])),(*reinterpret_cast< QString(*)>(_a[26])),(*reinterpret_cast< QString(*)>(_a[27])),(*reinterpret_cast< QString(*)>(_a[28])),(*reinterpret_cast< QString(*)>(_a[29])),(*reinterpret_cast< QString(*)>(_a[30])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->eliminarCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaDescripcionDeCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->retornaSiEsClienteWeb((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->retornaSiPermiteFacturaCredito((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->retornaDatoGenericoCliente((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloClientes::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloClientes::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloClientes,
      qt_meta_data_ModuloClientes, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloClientes::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloClientes::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloClientes::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloClientes))
        return static_cast<void*>(const_cast< ModuloClientes*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloClientes::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
