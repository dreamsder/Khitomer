/****************************************************************************
** Meta object code from reading C++ file 'moduloperfiles.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "moduloperfiles.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moduloperfiles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloPerfiles[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      25,   16,   15,   15, 0x02,
      49,   15,   15,   15, 0x02,
      83,   76,   72,   15, 0x02,
     105,   15,   72,   15, 0x22,
     136,  125,  116,   15, 0x02,
     164,  158,  116,   15, 0x22,
     184,  182,   15,   15, 0x02,
     236,  221,  216,   15, 0x02,
     283,   15,  275,   15, 0x02,
     317,   15,   72,   15, 0x02,
     342,   15,  216,   15, 0x02,
     653,  366,   72,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloPerfiles[] = {
    "ModuloPerfiles\0\0Perfiles\0"
    "agregarPerfil(Perfiles)\0limpiarListaPerfiles()\0"
    "int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0QVariant\0index,role\0"
    "data(QModelIndex,int)\0index\0"
    "data(QModelIndex)\0,\0buscarPerfiles(QString,QString)\0"
    "bool\0_codigoPerfil,\0"
    "retornaValorDePermiso(QString,QString)\0"
    "QString\0retornaDescripcionPerfil(QString)\0"
    "ultimoRegistroDePerfil()\0"
    "eliminarPerfil(QString)\0"
    ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,AccedeAlMenuUsuarios,AccedeAlMenuPermiso"
    "s,AccedeAlMenuMonedas,AccedeAlMenuRubros,AccedeAlMenuCuentasBancarias,"
    "AccedeAlMenuPagoDeFinacieras,AccedeAlMenuBancos,AccedeAlMenuLocalidade"
    "s,AccedeAlMenuTiposDeDocumentos,AccedeAlMenuIvas,AccedeAlMenuConfigura"
    "ciones\0"
    "insertarPerfil(QString,QString,QString,QString,QString,QString,QString"
    ",QString,QString,QString,QString,QString,QString,QString,QString,QStri"
    "ng,QString,QString,QString,QString,QString,QString,QString,QString,QSt"
    "ring,QString,QString,QString,QString,QString,QString,QString,QString,Q"
    "String,QString,QString,QString,QString,QString,QString,QString)\0"
};

void ModuloPerfiles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloPerfiles *_t = static_cast<ModuloPerfiles *>(_o);
        switch (_id) {
        case 0: _t->agregarPerfil((*reinterpret_cast< const Perfiles(*)>(_a[1]))); break;
        case 1: _t->limpiarListaPerfiles(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarPerfiles((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { bool _r = _t->retornaValorDePermiso((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaDescripcionPerfil((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->ultimoRegistroDePerfil();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->eliminarPerfil((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->insertarPerfil((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9])),(*reinterpret_cast< QString(*)>(_a[10])),(*reinterpret_cast< QString(*)>(_a[11])),(*reinterpret_cast< QString(*)>(_a[12])),(*reinterpret_cast< QString(*)>(_a[13])),(*reinterpret_cast< QString(*)>(_a[14])),(*reinterpret_cast< QString(*)>(_a[15])),(*reinterpret_cast< QString(*)>(_a[16])),(*reinterpret_cast< QString(*)>(_a[17])),(*reinterpret_cast< QString(*)>(_a[18])),(*reinterpret_cast< QString(*)>(_a[19])),(*reinterpret_cast< QString(*)>(_a[20])),(*reinterpret_cast< QString(*)>(_a[21])),(*reinterpret_cast< QString(*)>(_a[22])),(*reinterpret_cast< QString(*)>(_a[23])),(*reinterpret_cast< QString(*)>(_a[24])),(*reinterpret_cast< QString(*)>(_a[25])),(*reinterpret_cast< QString(*)>(_a[26])),(*reinterpret_cast< QString(*)>(_a[27])),(*reinterpret_cast< QString(*)>(_a[28])),(*reinterpret_cast< QString(*)>(_a[29])),(*reinterpret_cast< QString(*)>(_a[30])),(*reinterpret_cast< QString(*)>(_a[31])),(*reinterpret_cast< QString(*)>(_a[32])),(*reinterpret_cast< QString(*)>(_a[33])),(*reinterpret_cast< QString(*)>(_a[34])),(*reinterpret_cast< QString(*)>(_a[35])),(*reinterpret_cast< QString(*)>(_a[36])),(*reinterpret_cast< QString(*)>(_a[37])),(*reinterpret_cast< QString(*)>(_a[38])),(*reinterpret_cast< QString(*)>(_a[39])),(*reinterpret_cast< QString(*)>(_a[40])),(*reinterpret_cast< QString(*)>(_a[41])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloPerfiles::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloPerfiles::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloPerfiles,
      qt_meta_data_ModuloPerfiles, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloPerfiles::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloPerfiles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloPerfiles::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloPerfiles))
        return static_cast<void*>(const_cast< ModuloPerfiles*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloPerfiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
