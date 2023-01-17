/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

Este archivo es parte de Khitomer.

Khitomer es software libre: usted puede redistribuirlo y/o modificarlo
bajo los términos de la Licencia Pública General GNU publicada
por la Fundación para el Software Libre, ya sea la versión 3
de la Licencia, o (a su elección) cualquier versión posterior.

Este programa se distribuye con la esperanza de que sea útil, pero
SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita
MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO.
Consulte los detalles de la Licencia Pública General GNU para obtener
una información más detallada.

Debería haber recibido una copia de la Licencia Pública General GNU
junto a este programa.
En caso contrario, consulte <http://www.gnu.org/licenses/>.
*********************************************************************/

#include <QAbstractListModel>
#include <QStringList>

class Cliente
{
public:
   Q_INVOKABLE Cliente(const QString &codigoCliente, const int &tipoCliente, const QString &rut, const QString &nombreCliente,const QString &razonSocial,const QString &direccion,

                       const QString &esquina,const QString &numeroPuerta,const QString &telefono,const QString &telefono2,const QString &documento,const QString &codigoPostal,

                       const QString &email,const QString &sitioWeb,const QString &usuarioAlta,const QString &observaciones,const int &tipoClasificacion,

                       const int &codigoTipoCliente,const QString &descripcionTipoCliente,

                       const int &codigoTipoClasificacion,const QString &descripcionTipoClasificacion,

                       const QString &contacto,const QString &horario,

                       const int &codigoPais,const int &codigoDepartamento,const int &codigoLocalidad, const int &codigoTipoDocumentoCliente
                       , const int &codigoTipoProcedenciaCliente,

                       const QString &fechaNacimiento,
                       const QString &permiteFacturaCredito,
                       const int &codigoMonedaDefault,
                       const int &codigoFormasDePagoDefault,
                       const int &codigoTipoDocumentoDefault,
                       const QString &porcentajeDescuento
                       );




    QString codigoCliente() const;
    int tipoCliente() const;
    QString rut() const;
    QString nombreCliente() const;
    QString razonSocial() const;
    QString direccion() const;
    QString esquina() const;
    QString numeroPuerta() const;
    QString telefono() const;
    QString telefono2() const;
    QString documento() const;
    QString codigoPostal() const;
    QString email() const;
    QString sitioWeb() const;
    QString usuarioAlta() const;
    QString observaciones() const;
    int tipoClasificacion() const;
    int codigoTipoCliente() const;
    QString descripcionTipoCliente() const;
    int codigoTipoClasificacion() const;
    QString descripcionTipoClasificacion() const;
    QString contacto() const;
    QString horario() const;

    int codigoPais() const;
    int codigoDepartamento() const;
    int codigoLocalidad() const;

   int codigoTipoDocumentoCliente() const;

   int codigoTipoProcedenciaCliente() const;

   QString fechaNacimiento() const;
   QString permiteFacturaCredito() const;
   int codigoMonedaDefault() const;
   int codigoFormasDePagoDefault() const;
   int codigoTipoDocumentoDefault() const;
   QString porcentajeDescuento()const;

private:
    QString m_codigoCliente;
    int m_tipoCliente;
    QString m_rut;
    QString m_nombreCliente;
    QString m_razonSocial;
    QString m_direccion;
    QString m_esquina;
    QString m_numeroPuerta;
    QString m_telefono;
    QString m_telefono2;
    QString m_documento;
    QString m_codigoPostal;
    QString m_email;
    QString m_sitioWeb;
    QString m_usuarioAlta;
    QString m_observaciones;
    int m_tipoClasificacion;
    int m_codigoTipoCliente;
    QString m_descripcionTipoCliente;
    int m_codigoTipoClasificacion;
    QString m_descripcionTipoClasificacion;
    QString m_contacto;
    QString m_horario;

    int m_codigoPais;
    int m_codigoDepartamento;
    int m_codigoLocalidad;

    int m_codigoTipoDocumentoCliente;

    int m_codigoTipoProcedenciaCliente;
    QString m_fechaNacimiento;
    QString m_permiteFacturaCredito;
    int m_codigoMonedaDefault;
    int m_codigoFormasDePagoDefault;
    int m_codigoTipoDocumentoDefault;
    QString m_porcentajeDescuento;

};

class ModuloClientes : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ClienteRoles {
        CodigoClienteRole = Qt::UserRole + 1,
        TipoClienteRole,
        RutRole,
        NombreClienteRole,
        RazonSocialRole,
        DireccionRole,
        EsquinaRole,
        NumeroPuertaRole,
        TelefonoRole,
        Telefono2Role,
        DocumentoRole,
        CodigoPostalRole,
        EmailRole,
        SitioWebRole,
        UsuarioAltaRole,
        ObservacionesRole,
        TipoClasificacionRole,
        CodigoTipoClienteRole,
        DescripcionTipoClienteRole,
        CodigoTipoClasificacionRole,
        DescripcionTipoClasificacionRole,
        ContactoRole,
        HorarioRole,
        CodigoPaisRole,
        CodigoDepartamentoRole,
        CodigoLocalidadRole,
        codigoTipoDocumentoClienteRole,
        codigoTipoProcedenciaClienteRole,
        fechaNacimientoRole,
        permiteFacturaCreditoRole,
        codigoMonedaDefaultRole,
        codigoFormasDePagoDefaultRole,
        codigoTipoDocumentoDefaultRole,
        porcentajeDescuentoRole




    };

    ModuloClientes(QObject *parent = 0);

    Q_INVOKABLE void addCliente(const Cliente &Cliente);

    Q_INVOKABLE void clearClientes();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarCliente(QString , QString);

    Q_INVOKABLE qlonglong ultimoRegistroDeClienteEnBase(QString) const;

    Q_INVOKABLE qlonglong primerRegistroDeClienteEnBase() const;

    Q_INVOKABLE QString insertarCliente(QString , QString, QString , QString , QString , QString, QString , QString , QString

            , QString , QString , QString , QString , QString , QString

            , QString , QString, QString

            , QString , QString, QString
            , QString, QString, QString, QString, QString, QString, QString _codigoTipoDocumentoDefault,QString) const;

    Q_INVOKABLE bool eliminarCliente(QString , QString) const;

    Q_INVOKABLE QString retornaDescripcionDeCliente(QString , QString) const;

    Q_INVOKABLE bool retornaSiEsClienteWeb(QString ,QString ) const;

    Q_INVOKABLE bool retornaSiPermiteFacturaCredito(QString _codigoCliente,QString _tipoCliente) const;

    Q_INVOKABLE QString retornaDatoGenericoCliente(QString _codigoCliente,QString _tipoCliente, QString _campo) const;



private:
    QList<Cliente> m_Clientes;
};
