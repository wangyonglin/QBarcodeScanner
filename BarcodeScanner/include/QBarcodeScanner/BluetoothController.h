#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H
#include "QBarcodeScanner/Global.h"
#include "QBarcodeScanner/BluetoothDeviceDiscoveryAgent.h"
#include <QObject>
#include <QObject>
#include <QTimer>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QLowEnergyDescriptor>

namespace QBarcodeScanner{
class QBARCODESCANNER_EXPORT BluetoothController : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothController(QObject *parent = nullptr);
    ~BluetoothController();

    void CreateLowEnergyController(const QBluetoothDeviceInfo & deviceInfo);
private:

    QBluetoothDeviceInfo remoteBluetooth;
    QTimer keepAlive;
    QLowEnergyController::ControllerState remoteState;
    QLowEnergyController *controller = nullptr;
    QLowEnergyService *service = nullptr;
    QLowEnergyDescriptor descriptor;
    QList<QBluetoothUuid> uuids;
    QBluetoothUuid useuuid;
    QLowEnergyCharacteristic characteristic;
    QList<QLowEnergyCharacteristic> characteristics;
signals:
         // void fetchState(const QBluetoothAddress & remoteAddress,const QLowEnergyController::ControllerState &state);
    void OnCharacteristicRead(const QByteArray &data);
    void ControllerStateSignal(QLowEnergyController::ControllerState state);
public slots:

    void OnSlotState(QLowEnergyController::ControllerState state);
    void OnSlotError(QLowEnergyController::Error newError);
    void OnSlotConnected();
    void OnSlotDisconnect();
    void createServiceObject(const QBluetoothUuid &newService);


    void stateChanged(QLowEnergyService::ServiceState newState);
    void characteristicChanged(const QLowEnergyCharacteristic &info,
                               const QByteArray &value);
    void characteristicWritten(const QLowEnergyCharacteristic &info,
                               const QByteArray &value);
    void characteristicRead(const QLowEnergyCharacteristic &info,
                            const QByteArray &value);
    void OnSlotKeepAlive();
};
}
#endif // BLUETOOTHCONTROLLER_H
