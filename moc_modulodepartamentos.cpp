/****************************************************************************
** Meta object code from reading C++ file 'modulodepartamentos.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulodepartamentos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulodepartamentos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloDepartamentos[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      34,   21,   20,   20, 0x02,
      68,   20,   20,   20, 0x02,
     107,  100,   96,   20, 0x02,
     129,   20,   96,   20, 0x22,
     160,  149,  140,   20, 0x02,
     188,  182,  140,   20, 0x22,
     208,  206,   20,   20, 0x02,
     253,   20,  245,   20, 0x02,
     297,  294,   96,   20, 0x02,
     348,  206,  343,   20, 0x02,
     386,  206,  245,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloDepartamentos[] = {
    "ModuloDepartamentos\0\0Departamento\0"
    "agregarDepartamento(Departamento)\0"
    "limpiarListaDepartamentos()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarDepartamentos(QString,QString)\0"
    "QString\0retornaUltimoCodigoDepartamento(QString)\0"
    ",,\0insertarDepartamento(QString,QString,QString)\0"
    "bool\0eliminarDepartamento(QString,QString)\0"
    "retornaDescripcionDepartamento(QString,QString)\0"
};

void ModuloDepartamentos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloDepartamentos *_t = static_cast<ModuloDepartamentos *>(_o);
        switch (_id) {
        case 0: _t->agregarDepartamento((*reinterpret_cast< const Departamento(*)>(_a[1]))); break;
        case 1: _t->limpiarListaDepartamentos(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarDepartamentos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->retornaUltimoCodigoDepartamento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->insertarDepartamento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->eliminarDepartamento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaDescripcionDepartamento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloDepartamentos::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloDepartamentos::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloDepartamentos,
      qt_meta_data_ModuloDepartamentos, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloDepartamentos::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloDepartamentos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloDepartamentos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloDepartamentos))
        return static_cast<void*>(const_cast< ModuloDepartamentos*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloDepartamentos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
