TEMPLATE = lib
TARGET = BCharts
QT += qml quick
CONFIG += plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.balash.bcharts

# Input
SOURCES += \
    bcharts_plugin.cpp \
    bcharts.cpp \
    pie_chart/piechart.cpp \
    pie_chart/pieslice.cpp \
    base/basechart.cpp \
    base/baseseries.cpp

HEADERS += \
    bcharts_plugin.h \
    bcharts.h \
    pie_chart/piechart.h \
    pie_chart/pieslice.h \
    base/basechart.h \
    base/baseseries.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
