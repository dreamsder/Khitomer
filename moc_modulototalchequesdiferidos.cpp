/****************************************************************************
** Meta object code from reading C++ file 'modulototalchequesdiferidos.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulototalchequesdiferidos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulototalchequesdiferidos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloTotalChequesDiferidos[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      42,   29,   28,   28, 0x02,
      76,   28,   28,   28, 0x02,
     114,  107,  103,   28, 0x02,
     136,   28,  103,   28, 0x22,
     167,  156,  147,   28, 0x02,
     195,  189,  147,   28, 0x22,
     215,  213,   28,   28, 0x02,
     251,  213,   28,   28, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloTotalChequesDiferidos[] = {
    "ModuloTotalChequesDiferidos\0\0TotalCheques\0"
    "agregarTotalCheques(TotalCheques)\0"
    "limpiarListaTotalCheques()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarTotalCheques(QString,QString)\0"
    "buscarTotalOtrosCheques(QString,QString)\0"
};

void ModuloTotalChequesDiferidos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloTotalChequesDiferidos *_t = static_cast<ModuloTotalChequesDiferidos *>(_o);
        switch (_id) {
        case 0: _t->agregarTotalCheques((*reinterpret_cast< const TotalCheques(*)>(_a[1]))); break;
        case 1: _t->limpiarListaTotalCheques(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarTotalCheques((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->buscarTotalOtrosCheques((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloTotalChequesDiferidos::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloTotalChequesDiferidos::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloTotalChequesDiferidos,
      qt_meta_data_ModuloTotalChequesDiferidos, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloTotalChequesDiferidos::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloTotalChequesDiferidos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloTotalChequesDiferidos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloTotalChequesDiferidos))
        return static_cast<void*>(const_cast< ModuloTotalChequesDiferidos*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloTotalChequesDiferidos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
