QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    video.cpp

HEADERS += \
    mainwindow.h \
    video.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += C:/opencv/build/include

LIBS += -LC:/opencv/build/x64/mingw/lib \
        -lopencv_world455

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
