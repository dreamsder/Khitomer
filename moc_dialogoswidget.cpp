/****************************************************************************
** Meta object code from reading C++ file 'dialogoswidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Mantenimientos/dialogoswidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogoswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogosWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      24,   15,   16,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_DialogosWidget[] = {
    "DialogosWidget\0\0QString\0"
    "cargarArchivoMantenimiento(QString)\0"
};

void DialogosWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DialogosWidget *_t = static_cast<DialogosWidget *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->cargarArchivoMantenimiento((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DialogosWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DialogosWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DialogosWidget,
      qt_meta_data_DialogosWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogosWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogosWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogosWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogosWidget))
        return static_cast<void*>(const_cast< DialogosWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DialogosWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
