QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/сontroller_сalc.cc \
    Model/calculate.cc \
    Model/model.cc \
    View/graphic.cc \
    View/mainwindow.cc \
    main.cc \
    qcustomplot.cc

HEADERS += \
    Controller/controller_calc.h \
    Model/calculate.h \
    Model/credit_calculate.h \
    Model/model.h \
    View/graphic.h \
    View/mainwindow.h \
    qcustomplot.h

FORMS += \
    View/graphic.ui \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Model/a.out.dSYM/Contents/Info.plist \
    Model/a.out.dSYM/Contents/Resources/DWARF/a.out
