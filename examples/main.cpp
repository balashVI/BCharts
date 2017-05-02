#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../src/bcharts_plugin.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BChartsPlugin plugin;
    plugin.registerTypes("BVI.Charts");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
