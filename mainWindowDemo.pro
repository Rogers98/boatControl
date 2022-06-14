QT       += core gui webenginewidgets webchannel charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    altitudewidget.cpp \
    attitudewidget.cpp \
    getserialdata.cpp \
    main.cpp \
    mainwindow.cpp \
    panelwidget.cpp \
    speedwidget.cpp \
    speedwidget2.cpp \
    statewidget.cpp \
    statusview.cpp \
    statusview2.cpp \
    statusview3.cpp \
    statusviewrubbishboat.cpp \
    statusviewrubbishboat2.cpp \
    statusviewrubbishboat3.cpp \
    statuswidget.cpp \
    warnwidget.cpp

HEADERS += \
    altitudewidget.h \
    attitudewidget.h \
    getserialdata.h \
    mainwindow.h \
    panelwidget.h \
    speedwidget.h \
    speedwidget2.h \
    statewidget.h \
    statusview.h \
    statusview2.h \
    statusview3.h \
    statusviewrubbishboat.h \
    statusviewrubbishboat2.h \
    statusviewrubbishboat3.h \
    statuswidget.h \
    warnwidget.h

FORMS += \
    altitudewidget.ui \
    attitudewidget.ui \
    getserialdata.ui \
    mainwindow.ui \
    panelwidget.ui \
    speedwidget.ui \
    speedwidget2.ui \
    statewidget.ui \
    statusview.ui \
    statusview2.ui \
    statusview3.ui \
    statusviewrubbishboat.ui \
    statusviewrubbishboat2.ui \
    statusviewrubbishboat3.ui \
    statuswidget.ui \
    warnwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

#INCLUDEPATH+=/usr/local/include
#INCLUDEPATH+=/usr/local/include/VLCQtCore
#INCLUDEPATH+=/usr/local/include/VLCQtWidgets
#INCLUDEPATH+=/usr/local/include/VLCQtQml

#LIBS+=/usr/local/lib/libVLCQtCore.so.1.2
#LIBS+=/usr/local/lib/libVLCQtQml.so.1.2
#LIBS+=/usr/local/lib/libVLCQtWidgets.so.1.2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lVLCQtCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lVLCQtCore
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lVLCQtCore

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lVLCQtQml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lVLCQtQml
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lVLCQtQml

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lVLCQtWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lVLCQtWidgets
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lVLCQtWidgets

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so
