QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DirectNBodyProblemBH.cpp \
    InverseNBodyProblemBH.cpp \
    Star.cpp \
    main.cpp \
    window_sph_graph.cpp

HEADERS += \
    Constants.h \
    window_sph_graph.hpp

FORMS += \
    window_sph_graph.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
