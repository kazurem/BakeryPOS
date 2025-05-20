QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    Dashboard.cpp \
    Utils.cpp \
    main.cpp

HEADERS += \
    Dashboard.h \
    Utils.h \
    login.h

FORMS += \
    Dashboard.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    fonts/Poppins-Bold.ttf \
    fonts/Poppins-Italic.ttf \
    fonts/Poppins-Medium.ttf \
    fonts/Poppins-MediumItalic.ttf \
    fonts/Poppins-Regular.ttf \
    fonts/Poppins-SemiBold.ttf \
    fonts/Poppins-SemiBoldItalic.ttf \
    icons/search.png

