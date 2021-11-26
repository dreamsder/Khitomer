#include "waitingdlg.h"
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDialog>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLayout>



QProgressBar *progBar;
QLabel *lblMensajeError;


WaitingDlg::WaitingDlg(): QDialog(){
    mPrepareToClose=false;
}

WaitingDlg::WaitingDlg(const QString &labelText)
   : QDialog()
{
    mPrepareToClose=false;
   QVBoxLayout* layout = new QVBoxLayout(this);
   layout->addWidget(new QLabel(labelText));
   layout->addWidget(new QLabel("Aguarde..."));

   progBar = new QProgressBar();
   lblMensajeError = new QLabel("");

   lblMensajeError->setStyleSheet("QLabel { color : red; }");


   progBar->setTextVisible(true);
   progBar->setRange(1,350500);


   layout->addWidget(progBar);

   layout->addWidget(lblMensajeError);

   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle("Accesando...");
   setWindowOpacity(0.95);
   setWindowModality(Qt::ApplicationModal);
   setWindowFlags( ( (windowFlags() | Qt::CustomizeWindowHint)
                          & ~Qt::WindowCloseButtonHint) );

   setModal(true);
   setMaximumWidth(300);
   setMaximumHeight(100);
   setMinimumWidth(300);
   setMinimumHeight(100);

   QRect scr = QApplication::desktop()->screenGeometry(0);
   move( scr.center() - rect().center() );

   //setWindowFlags(Qt::FramelessWindowHint);

   /*  QDialog *dlg = new QDialog(NULL);
     QLabel *lbl = new QLabel(dlg);
     lbl->setText("Consultando la base de datos...");
     lbl->setMargin(20);
     dlg->setWindowTitle("Accesando...");
     dlg->setWindowFlags( ( (dlg->windowFlags() | Qt::CustomizeWindowHint)
                            & ~Qt::WindowCloseButtonHint) );


     //dlg->setWindowFlags(Qt::FramelessWindowHint);
     dlg->setWindowOpacity(0.9);

     dlg->setMaximumWidth(300);
     dlg->setMaximumHeight(100);
     dlg->setMinimumWidth(300);
     dlg->setMinimumHeight(100);

     dlg->setModal(true);
     dlg->show();
 */


}

/*void WaitingDlg::keyPressEvent(QKeyEvent *e)
{


   if (e->key() == Qt::Key_Escape)
      return;

   QDialog::keyPressEvent(e);
}

void WaitingDlg::closeEvent(QCloseEvent *e)
{
   if (!mPrepareToClose)
      e->ignore();
   else
      QDialog::closeEvent(e);
}*/

void WaitingDlg::close()
{
   mPrepareToClose = true;

   QDialog::close();
}

void WaitingDlg::setValorPbar(int i){
    progBar->setValue(i);
    if(i==40000){
        lblMensajeError->setText("ATENCIÓN:\n\nLa alta demora, indica problemas\nde conectividad o con el servidor.\nRevise la red y el servidor,\ny contacte al proveedor del software.");
    }
}
