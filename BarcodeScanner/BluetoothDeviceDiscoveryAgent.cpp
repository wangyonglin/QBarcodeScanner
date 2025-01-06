#include <QBarcodeScanner/BluetoothDeviceDiscoveryAgent.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QTimer>

#if QT_CONFIG(permissions)
#include <QCoreApplication>
#include <QPermissions>
#endif

QBarcodeScanner::BluetoothDeviceDiscoveryAgent::BluetoothDeviceDiscoveryAgent(QObject *parent):
    agent(new QBluetoothDeviceDiscoveryAgent(parent))
{
    // 设置搜索设备超时 20s
    agent->setLowEnergyDiscoveryTimeout(6000);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSlotDiscovered);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this, &QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSlotError);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSlotFinished);
}

QBarcodeScanner::BluetoothDeviceDiscoveryAgent::~BluetoothDeviceDiscoveryAgent()
{
    stop();
}

void QBarcodeScanner::BluetoothDeviceDiscoveryAgent::timeout(int msTimeout)
{
    agent->setLowEnergyDiscoveryTimeout(msTimeout);
}

void QBarcodeScanner::BluetoothDeviceDiscoveryAgent::start()
{
#if QT_CONFIG(permissions)
    //! [permissions]
    QBluetoothPermission permission{};
    permission.setCommunicationModes(QBluetoothPermission::Access);
    switch (qApp->checkPermission(permission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(permission, this, &QBarcodeScanner::BluetoothDeviceDiscoveryAgent::start);
        return;
    case Qt::PermissionStatus::Denied:
        qDebug() << "Bluetooth permissions not granted!";
        return;
    case Qt::PermissionStatus::Granted:
        break; // proceed to search
    }
    //! [permissions]
#endif // QT_CONFIG(permissions)
    agent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
     qDebug() << "QBluetoothStart";
}

void QBarcodeScanner::BluetoothDeviceDiscoveryAgent::stop()
{
    if(agent->isActive()){
        agent->stop();
    }
    qDebug() << "QBluetoothStop";
}

void QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSlotDiscovered(const QBluetoothDeviceInfo &info)
{
    if( info.isValid()){
        if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
            qDebug() << tr("bluetooth discovered deivce [%0 - %1]").arg(info.name()).arg(info.address().toString());
            emit OnSignalResolved(info);
        }
    }
}

void QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSlotError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError) {
        qDebug("Bluetooth power off");
    } else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError) {
        qDebug("Bluetooth input io error");
    } else {
        qDebug("Bluetooth other error");
    }
}

void QBarcodeScanner::BluetoothDeviceDiscoveryAgent::OnSlotFinished()
{
    qDebug() << "QBluetoothFinished";
}
