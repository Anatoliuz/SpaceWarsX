TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    myFunction.cpp \
    Network.cpp \
    calcModAdapter.cpp \
    calcMod/calculationmod.cpp \
    calcMod/building.cpp \
    calcMod/planet.cpp \
    calcMod/rib.cpp \
    calcMod/sector.cpp \
    calcMod/shell.cpp \
    calcMod/unit.cpp \
    datamodel.cpp \
    factory/fabrica.cpp \
    command/command.cpp \
    command/commandmove.cpp \
    command/commandProcessor.cpp \
    controller.cpp

HEADERS += \
    command.h \
    commandmove.h \
    myFunction.h \
    commandProcessor.h \
    client.h \
    Network.h \
    commands.h \
    config.h \
    concreteFabrics.h \
    factory.h \
    comMoveFactory.h \
    factories.h \
    includeMechanics.h \
    calcModAdapter.h \
    calcMod/calculationmod.h \
    calcMod/attacktype.h \
    calcMod/building.h \
    calcMod/coordinate_x_y.h \
    calcMod/includeMechanics.h \
    calcMod/movetype.h \
    calcMod/planet.h \
    calcMod/rib.h \
    calcMod/ribmovetype.h \
    calcMod/ribstruct.h \
    calcMod/sector.h \
    calcMod/shell.h \
    calcMod/unit.h \
    commandDoStep.h \
    comDoStepFactory.h \
    commandCreateBuilding.h \
    comCreateBuildingFactory.h \
    datamodel.h \
    factory/comCreateBuildingFactory.h \
    factory/comDoStepFactory.h \
    factory/comMoveFactory.h \
    factory/concreteFabrics.h \
    factory/factories.h \
    factory/factory.h \
    command/command.h \
    command/commandCreateBuilding.h \
    command/commandDoStep.h \
    command/commandmove.h \
    command/commandProcessor.h \
    command/commands.h \
    controller.h \
    commandWin.h \
    factory/comWinFactory.h

LIBS += -LC:/boost/lib\
-lboost_iostreams\
-lboost_system

LIBS+= -lpthread

QMAKE_CXXFLAGS += -std=c++0x

SUBDIRS += \
    calcMod/Geom_Wars.pro

OTHER_FILES += \
    calcMod/Geom_Wars.pro.user \
    calcMod/Geom_Wars.pro.user.18
