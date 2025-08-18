/****************************************************************************
** Meta object code from reading C++ file 'modulolistatipodocumentos.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulolistatipodocumentos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulolistatipodocumentos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuloListaTipoDocumentos[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      42,   27,   26,   26, 0x02,
      80,   26,   26,   26, 0x02,
     120,  113,  109,   26, 0x02,
     142,   26,  109,   26, 0x22,
     173,  162,  153,   26, 0x02,
     201,  195,  153,   26, 0x22,
     222,  219,   26,   26, 0x02,
     268,   26,   26,   26, 0x02,
     300,  298,   26,   26, 0x02,
     354,   26,  346,   26, 0x02,
     395,   26,  346,   26, 0x02,
     442,  298,  437,   26, 0x02,
     487,   26,  346,   26, 0x02,
     522,   26,  109,   26, 0x02,
     556,   26,  109,   26, 0x02,
     599,   26,  437,   26, 0x02,
     630,  298,   26,   26, 0x02,
     675,  298,   26,   26, 0x02,
     726,  720,  437,   26, 0x02,
     800,  756,  109,   26, 0x02,
    1175,  298,  346,   26, 0x02,
    1223,   26,  437,   26, 0x02,
    1263,  298,  437,   26, 0x02,
    1316,  219,  437,   26, 0x02,
    1413, 1392,  437,   26, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModuloListaTipoDocumentos[] = {
    "ModuloListaTipoDocumentos\0\0TipoDocumentos\0"
    "agregarTipoDocumentos(TipoDocumentos)\0"
    "limpiarListaTipoDocumentos()\0int\0"
    "parent\0rowCount(QModelIndex)\0rowCount()\0"
    "QVariant\0index,role\0data(QModelIndex,int)\0"
    "index\0data(QModelIndex)\0,,\0"
    "buscarTipoDocumentos(QString,QString,QString)\0"
    "buscarTipoDocumentosDefault()\0,\0"
    "buscarTodosLosTipoDocumentos(QString,QString)\0"
    "QString\0retornaDescripcionTipoDocumento(QString)\0"
    "retornaDescripcionCodigoADemanda(QString)\0"
    "bool\0retornaPermisosDelDocumento(QString,QString)\0"
    "retornaSerieTipoDocumento(QString)\0"
    "ultimoRegistroDeTipoDeDocumento()\0"
    "cantidadMaximaLineasTipoDocumento(QString)\0"
    "eliminarTipoDocumento(QString)\0"
    "insertarTipoDocumentoPerfil(QString,QString)\0"
    "eliminarTipoDocumentoPerfil(QString,QString)\0"
    "valor\0convertirStringABool(QString)\0"
    ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\0"
    "insertarTipoDocumento(QString,QString,QString,QString,QString,QString,"
    "QString,QString,QString,QString,QString,QString,QString,QString,QStrin"
    "g,QString,QString,QString,QString,QString,QString,QString,QString,QStr"
    "ing,QString,QString,QString,QString,QString,QString,QString,QString,QS"
    "tring,QString,QString,QString,QString,QString,QString,QString,QString,"
    "QString,QString,QString)\0"
    "retornaValorCampoTipoDocumento(QString,QString)\0"
    "permiteDevolucionTipoDocumento(QString)\0"
    "retornaDocumentoSegunMonedaRedondea(QString,QString)\0"
    "retornaPermiteModificacionMedioPagoPorDeudaContado(QString,QString,QSt"
    "ring)\0"
    "_codigoTipoDocumento\0"
    "esUnTipoDeDocumentoCreditoVenta(QString)\0"
};

void ModuloListaTipoDocumentos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuloListaTipoDocumentos *_t = static_cast<ModuloListaTipoDocumentos *>(_o);
        switch (_id) {
        case 0: _t->agregarTipoDocumentos((*reinterpret_cast< const TipoDocumentos(*)>(_a[1]))); break;
        case 1: _t->limpiarListaTipoDocumentos(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: _t->buscarTipoDocumentos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->buscarTipoDocumentosDefault(); break;
        case 8: _t->buscarTodosLosTipoDocumentos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: { QString _r = _t->retornaDescripcionTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->retornaDescripcionCodigoADemanda((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->retornaPermisosDelDocumento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->retornaSerieTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: { int _r = _t->ultimoRegistroDeTipoDeDocumento();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = _t->cantidadMaximaLineasTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->eliminarTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: _t->insertarTipoDocumentoPerfil((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: _t->eliminarTipoDocumentoPerfil((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: { bool _r = _t->convertirStringABool((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { int _r = _t->insertarTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9])),(*reinterpret_cast< QString(*)>(_a[10])),(*reinterpret_cast< QString(*)>(_a[11])),(*reinterpret_cast< QString(*)>(_a[12])),(*reinterpret_cast< QString(*)>(_a[13])),(*reinterpret_cast< QString(*)>(_a[14])),(*reinterpret_cast< QString(*)>(_a[15])),(*reinterpret_cast< QString(*)>(_a[16])),(*reinterpret_cast< QString(*)>(_a[17])),(*reinterpret_cast< QString(*)>(_a[18])),(*reinterpret_cast< QString(*)>(_a[19])),(*reinterpret_cast< QString(*)>(_a[20])),(*reinterpret_cast< QString(*)>(_a[21])),(*reinterpret_cast< QString(*)>(_a[22])),(*reinterpret_cast< QString(*)>(_a[23])),(*reinterpret_cast< QString(*)>(_a[24])),(*reinterpret_cast< QString(*)>(_a[25])),(*reinterpret_cast< QString(*)>(_a[26])),(*reinterpret_cast< QString(*)>(_a[27])),(*reinterpret_cast< QString(*)>(_a[28])),(*reinterpret_cast< QString(*)>(_a[29])),(*reinterpret_cast< QString(*)>(_a[30])),(*reinterpret_cast< QString(*)>(_a[31])),(*reinterpret_cast< QString(*)>(_a[32])),(*reinterpret_cast< QString(*)>(_a[33])),(*reinterpret_cast< QString(*)>(_a[34])),(*reinterpret_cast< QString(*)>(_a[35])),(*reinterpret_cast< QString(*)>(_a[36])),(*reinterpret_cast< QString(*)>(_a[37])),(*reinterpret_cast< QString(*)>(_a[38])),(*reinterpret_cast< QString(*)>(_a[39])),(*reinterpret_cast< QString(*)>(_a[40])),(*reinterpret_cast< QString(*)>(_a[41])),(*reinterpret_cast< QString(*)>(_a[42])),(*reinterpret_cast< QString(*)>(_a[43])),(*reinterpret_cast< QString(*)>(_a[44])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: { QString _r = _t->retornaValorCampoTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->permiteDevolucionTipoDocumento((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: { bool _r = _t->retornaDocumentoSegunMonedaRedondea((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 23: { bool _r = _t->retornaPermiteModificacionMedioPagoPorDeudaContado((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 24: { bool _r = _t->esUnTipoDeDocumentoCreditoVenta((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuloListaTipoDocumentos::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuloListaTipoDocumentos::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_ModuloListaTipoDocumentos,
      qt_meta_data_ModuloListaTipoDocumentos, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuloListaTipoDocumentos::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuloListaTipoDocumentos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuloListaTipoDocumentos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuloListaTipoDocumentos))
        return static_cast<void*>(const_cast< ModuloListaTipoDocumentos*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int ModuloListaTipoDocumentos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
