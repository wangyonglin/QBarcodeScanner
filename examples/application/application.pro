QT       += core gui opengl widgets bluetooth

# In Qt6 to use QOpenglWidget, we need add QT += openglwidgets.
greaterThan(QT_MAJOR_VERSION, 5){
    message(Building with Qt6 or Higher)
    QT += openglwidgets
}

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/../../BarcodeScanner/include

CONFIG += debug_and_release
linux-g++* {
    message(Compling with linux-g++)
    CONFIG(debug, debug|release){
        message(Debug build)
        message($$PWD)
        LIBS += -L$$PWD/../../build/Desktop_Qt_6_7_3-Debug/BarcodeScanner -lQBarcodeScanner

        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        LIBS += -L$$PWD/../../build/Desktop_Qt_6_7_3-Debug/BarcodeScanner -lQBarcodeScanner

    }

    DEFINES += CSM_TARGET_LINUX_GL
}


SOURCES += \
        QRootWidget.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    QRootWidget.h
