#include <QBarcodeScanner/BarcodeScanner.h>

QBarcodeScanner::BarcodeScanner::BarcodeScanner(QObject *parent)
{
    qBluetoothDeviceDiscoveryAgent = new QBarcodeScanner::BluetoothDeviceDiscoveryAgent(this);
    connect(qBluetoothDeviceDiscoveryAgent,&QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSignalResolved,
            this,&QBarcodeScanner::BarcodeScanner::OnSlostResolved);

    qBluetoothController= new QBarcodeScanner::BluetoothController(this);
    connect(qBluetoothController,&QBarcodeScanner::BluetoothController::OnCharacteristicRead,
            this,&QBarcodeScanner::BarcodeScanner::OnSlostCharacteristic);
}

QBarcodeScanner::BarcodeScanner::~BarcodeScanner()
{


}

void QBarcodeScanner::BarcodeScanner::pair(const QString &devicename)
{
    name=devicename;
    qBluetoothDeviceDiscoveryAgent->start();
}




void QBarcodeScanner::BarcodeScanner::OnSlostResolved(const QBluetoothDeviceInfo &deviceInfo)
{
    if (deviceInfo.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        // 添加对发现的BLE设备名称过滤，只保留需要名称的设备
        if (deviceInfo.isValid() && !name.isNull() && !name.isEmpty() &&  deviceInfo.name().contains(name))
        {
            qBluetoothController->CreateLowEnergyController(deviceInfo);
        }
    }


}

void QBarcodeScanner::BarcodeScanner::OnSlostCharacteristic(const QByteArray &data)
{
    emit OnSignalCharacteristic(data);
}
