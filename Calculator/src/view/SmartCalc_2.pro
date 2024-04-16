QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calc.cc \
    credit.cc \
    graph.cc \
    main.cc \
    ../controller/controller.cc \
    ../model/model_calculator.cc \
    ../model/model_creditcalc.cc


HEADERS += \
    calc.h \
    credit.h \
    graph.h \
    ../controller/controller.h \
    ../model/model_calculator.h \
    ../model/model_creditcalc.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
