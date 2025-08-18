/****************************************************************************
** Meta object code from reading C++ file 'controlesmantenimientos.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Mantenimientos/controlesmantenimientos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlesmantenimientos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlesMantenimientos[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      31,   25,   24,   24, 0x02,
      55,   24,   24,   24, 0x02,
      76,   69,   65,   24, 0x02,
      98,   24,   65,   24, 0x22,
     129,  118,  109,   24, 0x02,
     157,  151,  109,   24, 0x22,
     198,  180,  175,   24, 0x02,
     233,   24,   24,   24, 0x02,
     255,   25,  175,   24, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ControlesMantenimientos[] = {
    "ControlesMantenimientos\0\0valor\0"
    "agregar(Mantenimientos)\0limpiar()\0int\0"
    "parent\0rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0bool\0"
    "_permisoDocumento\0retornaValorMantenimiento(QString)\0"
    "buscarMantenimiento()\0"
    "convertirStringABool(QString)\0"
};

void ControlesMantenimientos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ControlesMantenimientos *_t = static_cast<ControlesMantenimientos *>(_o);
        switch (_id) {
        case 0: _t->agregar((*reinterpret_cast< const Mantenimientos(*)>(_a[1]))); break;
        case 1: _t->limpiar(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->retornaValorMantenimiento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->buscarMantenimiento(); break;
        case 8: { bool _r = _t->convertirStringABool((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ControlesMantenimientos::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ControlesMantenimientos::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ControlesMantenimientos,
      qt_meta_data_ControlesMantenimientos, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControlesMantenimientos::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControlesMantenimientos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControlesMantenimientos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlesMantenimientos))
        return static_cast<void*>(const_cast< ControlesMantenimientos*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ControlesMantenimientos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
