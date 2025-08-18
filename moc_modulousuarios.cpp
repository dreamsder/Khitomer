/****************************************************************************
** Meta object code from reading C++ file 'modulousuarios.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulousuarios.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulousuarios.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloUsuarios[] = {

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
      25,   16,   15,   15, 0x02,
      47,   15,   15,   15, 0x02,
      74,   67,   63,   15, 0x02,
      96,   15,   63,   15, 0x22,
     127,  116,  107,   15, 0x02,
     155,  149,  107,   15, 0x22,
     175,  173,   15,   15, 0x02,
     212,  173,  207,   15, 0x02,
     245,   15,  207,   15, 0x02,
     282,  270,   63,   15, 0x02,
     363,   15,  355,   15, 0x02,
     402,   15,  355,   15, 0x02,
     440,  173,   63,   15, 0x02,
     473,   15,  207,   15, 0x02,
     526,  515,  355,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloUsuarios[] = {
    "ModuloUsuarios\0\0Usuarios\0addUsuarios(Usuarios)\0"
    "clearUsuarios()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarUsuarios(QString,QString)\0bool\0"
    "conexionUsuario(QString,QString)\0"
    "eliminarUsuario(QString)\0,,,,,,email\0"
    "insertarUsuario(QString,QString,QString,QString,QString,QString,QStrin"
    "g)\0"
    "QString\0retornaVendedorSiEstaLogueado(QString)\0"
    "retornaNombreUsuarioLogueado(QString)\0"
    "actualizarClave(QString,QString)\0"
    "existenUsuariosConPerfilAsociado(QString)\0"
    "_idUsuario\0retornaCodigoPerfil(QString)\0"
};

void ModuloUsuarios::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloUsuarios *_t = static_cast<ModuloUsuarios *>(_o);
        switch (_id) {
        case 0: _t->addUsuarios((*reinterpret_cast< const Usuarios(*)>(_a[1]))); break;
        case 1: _t->clearUsuarios(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarUsuarios((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { bool _r = _t->conexionUsuario((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->eliminarUsuario((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->insertarUsuario((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaVendedorSiEstaLogueado((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornaNombreUsuarioLogueado((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->actualizarClave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->existenUsuariosConPerfilAsociado((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->retornaCodigoPerfil((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloUsuarios::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloUsuarios::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloUsuarios,
      qt_meta_data_ModuloUsuarios, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloUsuarios::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloUsuarios::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloUsuarios::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloUsuarios))
        return static_cast<void*>(const_cast< ModuloUsuarios*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloUsuarios::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
