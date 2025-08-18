/****************************************************************************
** Meta object code from reading C++ file 'modulogenericocombobox.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulogenericocombobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulogenericocombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloGenericoCombobox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      39,   24,   23,   23, 0x02,
      77,   23,   23,   23, 0x02,
     117,  110,  106,   23, 0x02,
     139,   23,  106,   23, 0x22,
     170,  159,  150,   23, 0x02,
     198,  192,  150,   23, 0x22,
     216,   23,   23,   23, 0x02,
     239,   23,   23,   23, 0x02,
     270,   23,   23,   23, 0x02,
     295,   23,   23,   23, 0x02,
     334,   23,  326,   23, 0x02,
     358,   23,  326,   23, 0x02,
     380,   23,  326,   23, 0x02,
     414,   23,  409,   23, 0x02,
     442,   23,  326,   23, 0x02,
     470,   23,  326,   23, 0x02,
     493,   23,  326,   23, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloGenericoCombobox[] = {
    "ModuloGenericoCombobox\0\0ModuloGenerico\0"
    "agregarModuloGenerico(ModuloGenerico)\0"
    "limpiarListaModuloGenerico()\0int\0"
    "parent\0rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0buscarModuloGenerico()\0"
    "buscarTodosLosTipoDocumentos()\0"
    "buscarTodosLosReportes()\0"
    "buscarTodosLosTiposPromocion()\0QString\0"
    "retornarCodigoItem(int)\0retornarSerieDoc(int)\0"
    "retornarDescripcionItem(int)\0bool\0"
    "retornarCheckBoxActivo(int)\0"
    "retornarCodigoTipoItem(int)\0"
    "retornarValorItem(int)\0"
    "retornarDescripcionItemSegundafila(int)\0"
};

void ModuloGenericoCombobox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloGenericoCombobox *_t = static_cast<ModuloGenericoCombobox *>(_o);
        switch (_id) {
        case 0: _t->agregarModuloGenerico((*reinterpret_cast< const ModuloGenerico(*)>(_a[1]))); break;
        case 1: _t->limpiarListaModuloGenerico(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarModuloGenerico(); break;
        case 7: _t->buscarTodosLosTipoDocumentos(); break;
        case 8: _t->buscarTodosLosReportes(); break;
        case 9: _t->buscarTodosLosTiposPromocion(); break;
        case 10: { QString _r = _t->retornarCodigoItem((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->retornarSerieDoc((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->retornarDescripcionItem((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->retornarCheckBoxActivo((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->retornarCodigoTipoItem((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { QString _r = _t->retornarValorItem((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->retornarDescripcionItemSegundafila((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloGenericoCombobox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloGenericoCombobox::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloGenericoCombobox,
      qt_meta_data_ModuloGenericoCombobox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloGenericoCombobox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloGenericoCombobox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloGenericoCombobox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloGenericoCombobox))
        return static_cast<void*>(const_cast< ModuloGenericoCombobox*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloGenericoCombobox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
