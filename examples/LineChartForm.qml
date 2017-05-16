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
                    data: [10, 20, 31,]
                    color: "#5C5C8A"
                    strokePen.color: "#7575A3"
                },LineSeries{
                    data: [15, 12, 21, 13, 15]
                    color: "#4Ca8d6"
                    strokePen.color: "#66CCFF"
                },LineSeries{
                    data: [25, 22, 11, 30, 18]
                    color: "#CC7A52"
                    strokePen.color: "#FF9966"
                }, LineSeries{
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

