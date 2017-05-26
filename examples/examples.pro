TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    ../src/charts/base_chart.cpp \
    ../src/charts/pie_chart.cpp \
    ../src/series/pie_slice.cpp \
    ../src/tools/stroke.cpp \
    ../src/abstractaxis.cpp \
    ../src/abstractchart.cpp \
    ../src/abstractseries.cpp \
    ../src/barchart.cpp \
    ../src/barseries.cpp \
    ../src/bcharts_plugin.cpp \
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
    ../src/xyseries.cpp \
    ../src/series/base_series.cpp \
    ../src/charts/polar_area_chart.cpp \
    ../src/series/polar_area.cpp \
    ../src/axes/base_axis.cpp \
    ../src/axes/linear_axis.cpp \
    ../src/grids/polar_grid.cpp \
    ../src/grids/base_grid.cpp \
    ../src/tools/label_configs.cpp \
    ../src/tools/calc.cpp \
    ../src/nodes/qsg_circle_node.cpp \
    ../src/nodes/qsg_smooth_color_material.cpp \
    ../src/nodes/qsg_smooth_color_material_shader.cpp \
    ../src/tools/grid_configs.cpp

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
    ../src/charts/base_chart.h \
    ../src/charts/pie_chart.h \
    ../src/series/pie_slice.h \
    ../src/tools/stroke.h \
    ../src/abstractaxis.h \
    ../src/abstractchart.h \
    ../src/abstractseries.h \
    ../src/barchart.h \
    ../src/barseries.h \
    ../src/bcharts_plugin.h \
    ../src/bubble.h \
    ../src/bubblechart.h \
    ../src/bubbleseries.h \
    ../src/categoryaxis.h \
    ../src/chartpen.h \
    ../src/chartpoint.h \
    ../src/linechart.h \
    ../src/lineseries.h \
    ../src/polarraxis.h \
    ../src/standartaxis.h \
    ../src/xychart.h \
    ../src/xyseries.h \
    ../src/series/base_series.h \
    ../src/charts/polar_area_chart.h \
    ../src/series/polar_area.h \
    ../src/axes/base_axis.h \
    ../src/axes/linear_axis.h \
    ../src/grids/polar_grid.h \
    ../src/grids/base_grid.h \
    ../src/tools/label_configs.h \
    ../src/tools/calc.h \
    ../src/nodes/qsg_circle_node.h \
    ../src/nodes/qsg_smooth_color_material.h \
    ../src/nodes/qsg_smooth_color_material_shader.h \
    ../src/tools/grid_configs.h

DISTFILES += \
    AllChartsForm.qml \
    BarChartForm.qml \
    BubbleChartForm.qml \
    ChartLegend.qml \
    LineChartForm.qml \
    main.qml \
    PieChartForm.qml \
    PolarAreaChartForm.qml \
    XYChartForm.qml
