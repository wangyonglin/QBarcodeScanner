#include "QRootWidget.h"
#include <QDebug>
#include <QKeyEvent>
QRootWidget::QRootWidget(QWidget *parent)
    : QWidget{parent}
{
    qBarcodeScanner= new QBarcodeScanner::BarcodeScanner(this);
    //("C barcode scanner");
    connect(qBarcodeScanner, &QBarcodeScanner::BarcodeScanner::OnSignalCharacteristic,this,[=](const QByteArray &data){
        qDebug() << "ddd" << data.constData();
    });
}

QRootWidget::~QRootWidget()
{


}

void QRootWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Tab:
        qBarcodeScanner->pair("C barcode scanner");
        break;
    default:
        break;
    }

}

