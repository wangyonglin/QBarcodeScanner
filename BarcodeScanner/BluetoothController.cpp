#include "QBarcodeScanner/BluetoothController.h"
//Resolved
#include <QThread>

QBarcodeScanner::BluetoothController::BluetoothController(QObject *parent)
    : QObject(parent)

{
   keepAlive.setInterval(300);
   connect(&keepAlive,&QTimer::timeout,this,&QBarcodeScanner::BluetoothController::OnSlotKeepAlive);
}

QBarcodeScanner::BluetoothController::~BluetoothController()
{

    if (controller) {
        controller->disconnectFromDevice();
        delete controller;
        controller = nullptr;
    }
}





void QBarcodeScanner::BluetoothController::CreateLowEnergyController(const QBluetoothDeviceInfo &deviceInfo)
{


        if(deviceInfo.isValid()){
            if(controller){ controller->disconnectFromDevice();}
            controller=QLowEnergyController::createCentral(deviceInfo,this);
            if(controller){
                controller->setRemoteAddressType(QLowEnergyController::RandomAddress);
                connect(controller, &QLowEnergyController::serviceDiscovered,
                        this, &QBarcodeScanner::BluetoothController::createServiceObject,Qt::DirectConnection);
                connect(controller, &QLowEnergyController::errorOccurred,
                        this,&QBarcodeScanner::BluetoothController::OnSlotError,Qt::DirectConnection);

                connect(controller, &QLowEnergyController::stateChanged,
                        this,&QBarcodeScanner::BluetoothController::OnSlotState,Qt::DirectConnection);

                connect(controller, &QLowEnergyController::connected,
                        this,&QBarcodeScanner::BluetoothController::OnSlotConnected,Qt::DirectConnection);
                connect(controller, &QLowEnergyController::disconnected,
                        this,&QBarcodeScanner::BluetoothController::OnSlotDisconnect,Qt::DirectConnection);
                QThread::msleep(1000);
                controller->connectToDevice();
                keepAlive.start();
        }
    }

}




void QBarcodeScanner::BluetoothController::OnSlotState(QLowEnergyController::ControllerState state)
{
    if(state == QLowEnergyController::ControllerState::ClosingState){
        qDebug() <<  tr("Bluetooth ClosingState state %1").arg(controller->remoteName());
      //  time.start();
    }else if(state == QLowEnergyController::ControllerState::ConnectedState){
          qDebug() <<  tr("Bluetooth ConnectedState state %1").arg(controller->remoteName());
      //  time.stop();
    }else if(state == QLowEnergyController::ControllerState::UnconnectedState){
          qDebug() <<  tr("Bluetooth UnconnectedState state %1").arg(controller->remoteName());
       // time.start();

    }
}

void QBarcodeScanner::BluetoothController::OnSlotError(QLowEnergyController::Error error)
{
    //Q_UNUSED(error);
    qDebug() << tr("bluetooth cannot connect to [%0 - %1]").arg(controller->remoteAddress().toString()).arg(error);
    if(remoteBluetooth.isValid() && error == QLowEnergyController::Error::UnknownError){

    }

}



void QBarcodeScanner::BluetoothController::OnSlotConnected()
{

    qDebug() << "bluetooth  connected" << controller->remoteName();
    controller->discoverServices();
    keepAlive.stop();

}

void QBarcodeScanner::BluetoothController::OnSlotDisconnect()
{
    qDebug() << "bluetooth  disconnected" << controller->remoteName();
    // controller->connectToDevice();
   keepAlive.start();


}

void QBarcodeScanner::BluetoothController::createServiceObject(const QBluetoothUuid &gatt)
{

    if(!gatt.isNull() && gatt==QBluetoothUuid( quint16(0xfff0))){
        qInfo() << "createServiceObject" << gatt.toString();
        if (service) {

            delete service;
            service = nullptr;
        }
        service = controller->createServiceObject(gatt, this);
        if (service) {
            connect(service, &QLowEnergyService::stateChanged,
                    this, &QBarcodeScanner::BluetoothController::stateChanged);
            connect(service, &QLowEnergyService::characteristicChanged,
                    this, &QBarcodeScanner::BluetoothController::characteristicChanged,Qt::DirectConnection);
            connect(service, &QLowEnergyService::characteristicRead,
                    this, &QBarcodeScanner::BluetoothController::characteristicRead);
            connect(service, &QLowEnergyService::characteristicWritten,
                    this, &QBarcodeScanner::BluetoothController::characteristicWritten);

            service->discoverDetails();

        }


    }

}




void QBarcodeScanner::BluetoothController::stateChanged(QLowEnergyService::ServiceState newState)
{
    QLowEnergyCharacteristic  batteryLevel;
    if(newState==QLowEnergyService::DiscoveringService){
        qInfo() << "Discovering services...";

    }else if(newState==QLowEnergyService::ServiceDiscovered){
        qInfo() << "Service discovered.";
        if(service){
            characteristics = service->characteristics();
            for(int i=0; i<characteristics.size(); i++){
                batteryLevel = characteristics.at(i);
                if(batteryLevel.isValid()){

                    descriptor = batteryLevel.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
                    if(descriptor.isValid()){
                        service->writeDescriptor(descriptor,QByteArray::fromHex("0100"));
                    }
                    if (batteryLevel.properties() & QLowEnergyCharacteristic::WriteNoResponse || batteryLevel.properties() & QLowEnergyCharacteristic::Write)
                    {

                        qDebug() << tr("%0 WriteNoResponse").arg(service->serviceName());
                        characteristic = batteryLevel;
                    }
                    if(batteryLevel.properties() & QLowEnergyCharacteristic::Read) {
                         qDebug() <<tr("%0 Read").arg(service->serviceName());

                        characteristic = batteryLevel;
                    }
                    if(batteryLevel.properties() & QLowEnergyCharacteristic::Notify) {
                         qDebug() << tr("%0 Notify").arg(service->serviceName());

                        characteristic = batteryLevel;
                    }
                }

            }
        }

    }else if(newState==QLowEnergyService::DiscoveryRequired){
         qDebug() << "DiscoveryRequired was renamed to RemoteService.";
    }

}

void QBarcodeScanner::BluetoothController::characteristicChanged(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    if(info.isValid() && !value.isNull()){
        emit OnCharacteristicRead(value);
    }

}

void QBarcodeScanner::BluetoothController::characteristicWritten(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    if (service)
    {
        if(characteristic.isValid()){
            service->writeCharacteristic(characteristic, value, QLowEnergyService::WriteWithResponse);
        }
    }
}


void QBarcodeScanner::BluetoothController::characteristicRead(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    if(info.isValid() && !value.isEmpty()){
        qDebug() << info.name()<< value.toStdString();
    }
}

void QBarcodeScanner::BluetoothController::OnSlotKeepAlive(){

    if(controller->state()!=QLowEnergyController::ControllerState::ConnectedState){
        controller->connectToDevice();
    }
}
