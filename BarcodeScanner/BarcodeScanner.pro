TEMPLATE = lib
QT       += core opengl bluetooth
#QT6LIBRARY_LIBRARY
linux-g++* {
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = QBarcodeScanner

        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = QBarcodeScanner


    }
    DEFINES += CSM_TARGET_LINUX_GL
}


INCLUDEPATH += include
SOURCES +=\
    BarcodeScanner.cpp \
    BluetoothController.cpp \
    BluetoothDeviceDiscoveryAgent.cpp \
    BluetoothService.cpp

HEADERS += \
    include/QBarcodeScanner/BarcodeScanner.h \
    include/QBarcodeScanner/BluetoothController.h \
    include/QBarcodeScanner/BluetoothDeviceDiscoveryAgent.h \
    include/QBarcodeScanner/BluetoothService.h \
    include/QBarcodeScanner/Global.h

