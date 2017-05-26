#include "bcharts_plugin.h"

#include <qqml.h>

#include "axes/base_axis.h"

#include "charts/polar_area_chart.h"
#include "charts/pie_chart.h"

#include "series/polar_area.h"
#include "series/pie_slice.h"

#include "tools/label_configs.h"
#include "tools/grid_configs.h"
#include "tools/stroke.h"

#include "barchart.h"
#include "barseries.h"
#include "categoryaxis.h"
#include "chartpen.h"
#include "standartaxis.h"
#include "polarraxis.h"
#include "lineseries.h"
#include "linechart.h"
#include "chartpoint.h"
#include "xyseries.h"
#include "xychart.h"
#include "bubble.h"
#include "bubblechart.h"
#include "bubbleseries.h"

void BChartsPlugin::registerTypes(const char *uri)
{
    // @uri com.balash.bcharts
    qmlRegisterUncreatableType<BaseAxis>(uri, 2, 0, "BaseAxis", "");

    qmlRegisterType<PieChart>(uri, 2, 0, "PieChart");
    qmlRegisterType<PolarAreaChart>(uri, 2, 0, "PolarAreaChart");

    qmlRegisterType<PieSlice>(uri, 2, 0, "PieSlice");
    qmlRegisterType<PolarArea>(uri, 2, 0, "PolarArea");

    qmlRegisterUncreatableType<Stroke>(uri, 2, 0, "Stroke", "");
    qmlRegisterUncreatableType<LabelConfigs>(uri, 2, 0, "LabelConfigs", "");
    qmlRegisterUncreatableType<GridConfigs>(uri, 2, 0, "GridConfigs", "");

    qmlRegisterType<Bubble>(uri, 1, 0, "Bubble");
    qmlRegisterType<BubbleSeries>(uri, 1, 0, "BubbleSeries");
    qmlRegisterType<BubbleChart>(uri, 1, 0, "BubbleChart");
    qmlRegisterType<XYChart>(uri, 1, 0, "XYChart");
    qmlRegisterType<XYSeries>(uri, 1, 0, "XYSeries");
    qmlRegisterType<ChartPoint>(uri, 1, 0, "ChartPoint");
    qmlRegisterType<LineChart>(uri, 1, 0, "LineChart");
    qmlRegisterType<LineSeries>(uri, 1, 0, "LineSeries");
    qmlRegisterType<PolarRAxis>(uri, 1, 0, "PolarRAxis");
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
    qmlRegisterType<PieChart>(uri, 1, 0, "PieChart");
    qmlRegisterType<BarChart>(uri, 1, 0, "BarChart");
    qmlRegisterType<BarSeries>(uri, 1, 0, "BarSeries");
    qmlRegisterType<CategoryAxis>(uri, 1, 0, "CategoryAxis");
    qmlRegisterType<StandartAxis>(uri, 1, 0, "StandartAxis");
    qmlRegisterType<ChartPen>(uri, 1, 0, "ChartPen");
}
