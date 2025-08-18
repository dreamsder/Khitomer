/****************************************************************************
** Meta object code from reading C++ file 'moduloreportesmenu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloreportesmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloreportesmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloReportesMenu[] = {

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
      33,   20,   19,   19, 0x02,
      66,   19,   19,   19, 0x02,
     104,   97,   93,   19, 0x02,
     126,   19,   93,   19, 0x22,
     157,  146,  137,   19, 0x02,
     185,  179,  137,   19, 0x22,
     206,  203,   19,   19, 0x02,
     258,   19,  250,   19, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloReportesMenu[] = {
    "ModuloReportesMenu\0\0ReportesMenu\0"
    "agregarReporteMenu(ReportesMenu)\0"
    "limpiarListaReportesMenu()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,,\0"
    "buscarReportesMenu(QString,QString,QString)\0"
    "QString\0listaCodigoMenusPorPerfil(QString)\0"
};

void ModuloReportesMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloReportesMenu *_t = static_cast<ModuloReportesMenu *>(_o);
        switch (_id) {
        case 0: _t->agregarReporteMenu((*reinterpret_cast< const ReportesMenu(*)>(_a[1]))); break;
        case 1: _t->limpiarListaReportesMenu(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarReportesMenu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: { QString _r = _t->listaCodigoMenusPorPerfil((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloReportesMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloReportesMenu::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloReportesMenu,
      qt_meta_data_ModuloReportesMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloReportesMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloReportesMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloReportesMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloReportesMenu))
        return static_cast<void*>(const_cast< ModuloReportesMenu*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloReportesMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
