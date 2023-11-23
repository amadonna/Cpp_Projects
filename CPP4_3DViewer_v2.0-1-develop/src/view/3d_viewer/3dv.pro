QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += fsanitize=address

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../main.cc \
    widget.cc \
    ../../model/transform/transformation.cc \
    ../../model/parcer/parcer.cc \
    ../../model/normalization/normalization.cc \
    ../../model/model_facade.cc \
    ../../controller/controller_singleton.cc \

HEADERS += \
    widget.h \
    ../../model/transform/transformation.h \
    ../../model/parcer/parcer.h \
    ../../model/data/data_model.h \
    ../../model/normalization/normalization.h \
    ../../model/model_facade.h \
    ../../controller/controller_singleton.h

FORMS += \
    widget.ui

LIBS += -framework OpenGL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
