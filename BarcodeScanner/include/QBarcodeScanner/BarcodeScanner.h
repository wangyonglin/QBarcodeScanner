#ifndef BARCODESCANNER_H
#define BARCODESCANNER_H
#include "QBarcodeScanner/Global.h"
#include <QObject>
#include "QBarcodeScanner/BluetoothDeviceDiscoveryAgent.h"
#include "QBarcodeScanner/BluetoothService.h"
#include "QBarcodeScanner/BluetoothController.h"

QT_BEGIN_NAMESPACE
class QBluetoothDeviceInfo;
QT_END_NAMESPACE


namespace QBarcodeScanner {
class DeviceInfo;
class QBARCODESCANNER_EXPORT BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeScanner(QObject *parent = nullptr);
    ~BarcodeScanner();
    void pair(const QString & devicename);
private:
    QList<QBluetoothDeviceInfo> listDevices;
    QString name;
    BluetoothDeviceDiscoveryAgent *qBluetoothDeviceDiscoveryAgent;
    BluetoothController * qBluetoothController;
signals:
    void OnSignalCharacteristic(const QByteArray &data);
public slots:
    void OnSlostResolved(const QBluetoothDeviceInfo &info);
    void OnSlostCharacteristic(const QByteArray &data);
};
}
#endif // BARCODESCANNER_H
