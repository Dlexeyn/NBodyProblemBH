QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GausNewtonSolver.cpp \
    NBodyProblemBHSolver.cpp \
    Structures/ModelValue.cpp \
    Structures/SimulationVector.cpp \
    Structures/Star.cpp \
    Structures/Matrix.cpp \
    Structures/VectorsOperations.cpp \
    main.cpp \
    Graphics/window_sph_graph.cpp

HEADERS += \
    GausNewtonSolver.hpp \
    Options/Constants.h \
    Structures/ModelValue.hpp \
    Structures/SimulationVector.hpp \
    Structures/Matrix.h \
    Structures/VectorsOperations.hpp \
    Graphics/window_sph_graph.hpp

FORMS += \
    Graphics/window_sph_graph.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
