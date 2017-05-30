import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Layouts 1.1

Rectangle {
    RowLayout{
        anchors.fill: parent

        BarChart{
            id: barChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            xAxis.labels: ["first", "second", "third", "fourth"]
            series: [BarSeries{
                    name: "First"
                    data: [10, 20, 31]
                    color: "#aa7575A3"
                    strokePen.color: "#5C5C8A"
                },BarSeries{
                    name: "Second"
                    data: [15, 12, 21, 13]
                    color: "#aa66CCFF"
                    strokePen.color: "#4Ca8d6"
                },BarSeries{
                    name: "Third"
                    data: [25, 22, 11, 30]
                    color: "#aaFF9966"
                    strokePen.color: "#CC7A52"
                }, BarSeries{
                    name: "Fourth"
                    data: [23,18,43,35]
                    color: "#aa4C996B"
                    strokePen.color: "#3C895B"
                }
            ]
        }
        ChartLegend{
            Layout.fillHeight: true
            source: barChart
        }
    }
}

