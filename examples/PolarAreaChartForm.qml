import QtQuick 2.4
import BVI.Charts 2.0
import QtQuick.Layouts 1.1

Rectangle {

    RowLayout{
        anchors.fill: parent
        PolarAreaChart{
            id: polarAreaChart
            Layout.fillHeight: true
            Layout.fillWidth: true

            PolarArea{
                name: "First"
                color: "#FF9966"
                value: 10
            }
            PolarArea{
                name: "Second"
                color: "#66CCFF"
                value: 20
            }
            PolarArea{
                name: "Third"
                color: "#3C895B"
                value: 15
            }
            PolarArea{
                name: "Fourth"
                color: "#7575A3"
                value: 25
            }
        }
        ChartLegend{
            Layout.fillHeight: true
            source: polarAreaChart
        }
    }
}

