TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    ../src/base/basechart.cpp \
    ../src/base/baseseries.cpp \
    ../src/pie_chart/piechart.cpp \
    ../src/pie_chart/pieslice.cpp \
    ../src/bcharts_plugin.cpp \
    ../src/pie_chart/stroke.cpp \
    ../src/abstractaxis.cpp \
    ../src/abstractchart.cpp \
    ../src/abstractseries.cpp \
    ../src/barchart.cpp \
    ../src/barseries.cpp \
    ../src/bubble.cpp \
    ../src/bubblechart.cpp \
    ../src/bubbleseries.cpp \
    ../src/categoryaxis.cpp \
    ../src/chartpen.cpp \
    ../src/chartpoint.cpp \
    ../src/linechart.cpp \
    ../src/lineseries.cpp \
    ../src/polarraxis.cpp \
    ../src/standartaxis.cpp \
    ../src/xychart.cpp \
    ../src/xyseries.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../src/base/basechart.h \
    ../src/base/baseseries.h \
    ../src/pie_chart/piechart.h \
    ../src/pie_chart/pieslice.h \
    ../src/bcharts_plugin.h \
    ../src/pie_chart/stroke.h \
    ../src/abstractaxis.h \
    ../src/abstractchart.h \
    ../src/abstractseries.h \
    ../src/barchart.h \
    ../src/barseries.h \
    ../src/bubble.h \
    ../src/bubblechart.h \
    ../src/bubbleseries.h \
    ../src/categoryaxis.h \
    ../src/chartpen.h \
    ../src/linechart.h \
    ../src/lineseries.h \
    ../src/polarraxis.h \
    ../src/standartaxis.h \
    ../src/xychart.h \
    ../src/xyseries.h \
    ../src/chartpoint.h
