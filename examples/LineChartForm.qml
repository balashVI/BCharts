import QtQuick 2.4
import QtQuick.Layouts 1.1
import BVI.Charts 1.0

Rectangle {
    color: "white"
    RowLayout{
        anchors.fill: parent
        LineChart{
            id: lineChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            xAxis.labels: ["first", "second", "third", "fourth", "fifth"]
            series: [
                LineSeries{
                    name: "First"
                    data: [10, 20, 31,]
                    color: "#5C5C8A"
                    strokePen.color: "#7575A3"
                },LineSeries{
                    name: "Second"
                    data: [15, 12, 21, 13, 15]
                    color: "#4Ca8d6"
                    strokePen.color: "#66CCFF"
                },LineSeries{
                    name: "Third"
                    data: [25, 22, 11, 30, 18]
                    color: "#CC7A52"
                    strokePen.color: "#FF9966"
                }, LineSeries{
                    name: "Fourth"
                    data: [30,25,43,35, 20]
                    color: "#3C895B"
                    strokePen.color: "#4C996B"
                }

            ]

        }
        ChartLegend{
            Layout.fillHeight: true
            source: lineChart
        }
    }
}

