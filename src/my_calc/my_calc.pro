QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
		../back_calc/back_calc.cpp \
		../controller_calc/controllerCalc.cpp \
	../view_calc/graph/qcustomplot.cpp \
    main.cpp \
		../view_calc/graph/graph.cpp \
		../view_calc/viewCalc.cpp

HEADERS += \
    ../back_calc/back_calc.h \
		../back_calc/back_calc.h \
		../controller_calc/controllerCalc.h \
		../view_calc/graph/graph.h \
	../view_calc/graph/qcustomplot.h \
		../view_calc/viewCalc.h

FORMS += \
 ../view_calc/graph/graph.ui \
 ../view_calc/viewCalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
