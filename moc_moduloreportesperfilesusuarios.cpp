/****************************************************************************
** Meta object code from reading C++ file 'moduloreportesperfilesusuarios.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloreportesperfilesusuarios.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloreportesperfilesusuarios.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloReportesPerfilesUsuarios[] = {

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
      57,   32,   31,   31, 0x02,
      91,   31,   31,   31, 0x02,
     112,  105,  101,   31, 0x02,
     134,   31,  101,   31, 0x22,
     165,  154,  145,   31, 0x02,
     193,  187,  145,   31, 0x22,
     211,   31,   31,   31, 0x02,
     251,  249,  244,   31, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloReportesPerfilesUsuarios[] = {
    "ModuloReportesPerfilesUsuarios\0\0"
    "ReportesPerfilesUsuarios\0"
    "agregar(ReportesPerfilesUsuarios)\0"
    "limpiar()\0int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0QVariant\0index,role\0"
    "data(QModelIndex,int)\0index\0"
    "data(QModelIndex)\0buscarReportesPerfilesUsuarios()\0"
    "bool\0,\0retornaReporteActivoPorPerfil(QString,QString)\0"
};

void ModuloReportesPerfilesUsuarios::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloReportesPerfilesUsuarios *_t = static_cast<ModuloReportesPerfilesUsuarios *>(_o);
        switch (_id) {
        case 0: _t->agregar((*reinterpret_cast< const ReportesPerfilesUsuarios(*)>(_a[1]))); break;
        case 1: _t->limpiar(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarReportesPerfilesUsuarios(); break;
        case 7: { bool _r = _t->retornaReporteActivoPorPerfil((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloReportesPerfilesUsuarios::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloReportesPerfilesUsuarios::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloReportesPerfilesUsuarios,
      qt_meta_data_ModuloReportesPerfilesUsuarios, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloReportesPerfilesUsuarios::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloReportesPerfilesUsuarios::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloReportesPerfilesUsuarios::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloReportesPerfilesUsuarios))
        return static_cast<void*>(const_cast< ModuloReportesPerfilesUsuarios*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloReportesPerfilesUsuarios::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
