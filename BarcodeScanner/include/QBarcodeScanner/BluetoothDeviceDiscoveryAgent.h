#ifndef BLUETOOTHDEVICEDISCOVERYAGENT_H
#define BLUETOOTHDEVICEDISCOVERYAGENT_H
#include "QBarcodeScanner/Global.h"
#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QBluetoothDeviceInfo;
QT_END_NAMESPACE


namespace QBarcodeScanner {
class DeviceInfo;
class QBARCODESCANNER_EXPORT BluetoothDeviceDiscoveryAgent : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothDeviceDiscoveryAgent(QObject *parent = nullptr);
    ~BluetoothDeviceDiscoveryAgent();
    void timeout(int msTimeout=6000);
    void start();
    void stop();
public slots:
    void OnSlotDiscovered(const QBluetoothDeviceInfo &info);
    void OnSlotError(QBluetoothDeviceDiscoveryAgent::Error error);
    void OnSlotFinished();
signals:
    void OnSignalResolved(const QBluetoothDeviceInfo &info);
private:
    QBluetoothDeviceDiscoveryAgent *agent;
};


}
#endif // BLUETOOTHDEVICEDISCOVERYAGENT_H
