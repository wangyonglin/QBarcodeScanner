#ifndef QROOTWIDGET_H
#define QROOTWIDGET_H

#include <QWidget>
#include "QBarcodeScanner/BarcodeScanner.h"

class QRootWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QRootWidget(QWidget *parent = nullptr);
    ~QRootWidget();
    QBarcodeScanner::BarcodeScanner *qBarcodeScanner;
signals:
public slots:


    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // QROOTWIDGET_H
