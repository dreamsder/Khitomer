/****************************************************************************
** Meta object code from reading C++ file 'utilidadesdemenu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Utilidades/utilidadesdemenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'utilidadesdemenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UtilidadesDeMenu[] = {

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
      24,   18,   17,   17, 0x02,
      43,   17,   17,   17, 0x02,
      74,   67,   63,   17, 0x02,
      96,   17,   63,   17, 0x22,
     127,  116,  107,   17, 0x02,
     155,  149,  107,   17, 0x22,
     175,  173,   17,   17, 0x02,
     204,   17,   63,   17, 0x02,
     235,   17,  227,   17, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_UtilidadesDeMenu[] = {
    "UtilidadesDeMenu\0\0Menus\0agregarMenu(Menus)\0"
    "limpiarListaMenus()\0int\0parent\0"
    "rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,\0"
    "buscarMenus(QString,QString)\0"
    "retornaCodigoMenu(int)\0QString\0"
    "retornaNombreMenu(int)\0"
};

void UtilidadesDeMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UtilidadesDeMenu *_t = static_cast<UtilidadesDeMenu *>(_o);
        switch (_id) {
        case 0: _t->agregarMenu((*reinterpret_cast< const Menus(*)>(_a[1]))); break;
        case 1: _t->limpiarListaMenus(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarMenus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { int _r = _t->retornaCodigoMenu((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->retornaNombreMenu((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UtilidadesDeMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UtilidadesDeMenu::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_UtilidadesDeMenu,
      qt_meta_data_UtilidadesDeMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UtilidadesDeMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UtilidadesDeMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UtilidadesDeMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UtilidadesDeMenu))
        return static_cast<void*>(const_cast< UtilidadesDeMenu*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int UtilidadesDeMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
