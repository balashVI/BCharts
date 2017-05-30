import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("BCharts example")
    width: 1040
    height: 680
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Тип графіка")
            MenuItem {
                text: qsTr("AllCharts")
                onTriggered: loader.source = "AllChartsForm.qml"
            }
            MenuItem {
                text: qsTr("LineChart")
                onTriggered: loader.source = "LineChartForm.qml"
            }
            MenuItem {
                text: qsTr("BarChart")
                onTriggered: loader.source = "BarChartForm.qml"
            }
            MenuItem {
                text: qsTr("PieChart")
                onTriggered: loader.source = "PieChartForm.qml"
            }
            MenuItem {
                text: qsTr("PolarAreaChart")
                onTriggered: loader.source = "PolarAreaChartForm.qml"
            }
            MenuItem {
                text: qsTr("XYChart")
                onTriggered: loader.source = "XYChartForm.qml"
            }
            MenuItem {
                text: qsTr("BubbleChart")
                onTriggered: loader.source = "BubbleChartForm.qml"
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
        active: true
        source: "AllChartsForm.qml"
    }
}
