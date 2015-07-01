TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QT =

unix {
CONFIG += link_pkgconfig
PKGCONFIG += libAthena
}
#dnaTarget.target = DNA_dat.cpp
#dnaTarget.depends = $$PWD/DNA_dat.hpp
#dnaTarget.commands = atdna -o DNA_dat.cpp $$PWD/DNA_dat.hpp
#PRE_TARGETDEPS += DNA_dat.cpp
#QMAKE_EXTRA_TARGETS += dnaTarget

HEADERS += \
    DNA_dat.hpp \
    DNA_pc.hpp

SOURCES += \
    main.cpp \
    DNA_dat.cpp \
    DNA_pc.cpp
