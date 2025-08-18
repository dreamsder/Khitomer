/****************************************************************************
** Meta object code from reading C++ file 'moduloreportesconfiguracion.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloreportesconfiguracion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloreportesconfiguracion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloReportesConfiguracion[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      51,   29,   28,   28, 0x02,
      82,   28,   28,   28, 0x02,
     103,   96,   92,   28, 0x02,
     125,   28,   92,   28, 0x22,
     156,  145,  136,   28, 0x02,
     184,  178,  136,   28, 0x22,
     202,   28,   28,   28, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloReportesConfiguracion[] = {
    "ModuloReportesConfiguracion\0\0"
    "ReportesConfiguracion\0"
    "agregar(ReportesConfiguracion)\0limpiar()\0"
    "int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0QVariant\0index,role\0"
    "data(QModelIndex,int)\0index\0"
    "data(QModelIndex)\0buscarReportesConfiguracion()\0"
};

void ModuloReportesConfiguracion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloReportesConfiguracion *_t = static_cast<ModuloReportesConfiguracion *>(_o);
        switch (_id) {
        case 0: _t->agregar((*reinterpret_cast< const ReportesConfiguracion(*)>(_a[1]))); break;
        case 1: _t->limpiar(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarReportesConfiguracion(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloReportesConfiguracion::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloReportesConfiguracion::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloReportesConfiguracion,
      qt_meta_data_ModuloReportesConfiguracion, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloReportesConfiguracion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloReportesConfiguracion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloReportesConfiguracion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloReportesConfiguracion))
        return static_cast<void*>(const_cast< ModuloReportesConfiguracion*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloReportesConfiguracion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
