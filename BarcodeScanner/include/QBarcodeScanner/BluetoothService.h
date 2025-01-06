// #ifndef BLUETOOTHSERVICE_H
// #define BLUETOOTHSERVICE_H
// #include "QBarcodeScanner/Global.h"
// #include <QObject>
// #include <QTimer>
// #include <QBluetoothDeviceInfo>
// #include <QLowEnergyController>
// #include <QLowEnergyService>
// #include <QLowEnergyDescriptor>
// #include "QBarcodeScanner/BluetoothController.h"

// namespace QBarcodeScanner{
// class QBARCODESCANNER_EXPORT BluetoothService : public QObject
// {
//     Q_OBJECT

// public:
//     explicit BluetoothService(QObject *parent = nullptr);
//     ~BluetoothService();
//     void CreateService(QBarcodeScanner::BluetoothController * contrller);
//     void createCentral(const QBluetoothDeviceInfo &remoteDevice);
//     void release();

// private:
//     QBluetoothDeviceInfo remoteBluetooth;
//     QTimer time;
//     QLowEnergyController::ControllerState remoteState;
//     QLowEnergyController *controller = nullptr;
//     QLowEnergyService *service = nullptr;
//     QLowEnergyDescriptor descriptor;
//     QList<QBluetoothUuid> uuids;
//     QBluetoothUuid useuuid;
//     QLowEnergyCharacteristic characteristic;
//     QList<QLowEnergyCharacteristic> characteristics;
// signals:
//          // void fetchState(const QBluetoothAddress & remoteAddress,const QLowEnergyController::ControllerState &state);
//     void OnCharacteristicRead(const QByteArray &data);
//     void ControllerStateSignal(QLowEnergyController::ControllerState state);
// public slots:

//     void OnSlotState(QLowEnergyController::ControllerState state);
//     void OnSlotError(QLowEnergyController::Error newError);
//     void OnSlotConnected();
//     void OnSlotDisconnect();
//     void createServiceObject(const QBluetoothUuid &newService);


//     void stateChanged(QLowEnergyService::ServiceState newState);
//     void characteristicChanged(const QLowEnergyCharacteristic &info,
//                                const QByteArray &value);
//     void characteristicWritten(const QLowEnergyCharacteristic &info,
//                                const QByteArray &value);
//     void characteristicRead(const QLowEnergyCharacteristic &info,
//                             const QByteArray &value);
//     void keepAlive();
// };
// }


// #endif // BLUETOOTHSERVICE_H
