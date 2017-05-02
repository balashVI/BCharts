#include "bcharts_plugin.h"

#include <qqml.h>

#include "pie_chart/piechart.h"
#include "pie_chart/pieslice.h"

void BChartsPlugin::registerTypes(const char *uri)
{
    // @uri com.balash.bcharts
    qmlRegisterType<PieChart>(uri, 1, 0, "PieChart");
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
}

