QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += BakeryPOS/include

SOURCES += \
    BakeryPOS/src/AddProductForm.cpp \
    BakeryPOS/src/Dashboard.cpp \
    BakeryPOS/src/EditProductForm.cpp \
    BakeryPOS/src/Login.cpp \
    BakeryPOS/src/Main.cpp \
    BakeryPOS/src/Utils.cpp

HEADERS += \
    BakeryPOS/include/AddProductForm.h \
    BakeryPOS/include/Dashboard.h \
    BakeryPOS/include/EditProductForm.h \
    BakeryPOS/include/Login.h \
    BakeryPOS/include/Utils.h

FORMS += \
    BakeryPOS/ui/AddProductForm.ui \
    BakeryPOS/ui/Dashboard.ui \
    BakeryPOS/ui/EditProductForm.ui \
    BakeryPOS/ui/Login.ui

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

