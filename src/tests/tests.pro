TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

CONFIG += link_pkgconfig
PKGCONFIG += gtest

SOURCES += \
        ../back_calc/back_calc.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	../back_calc/back_calc.h \
        test_back.h

