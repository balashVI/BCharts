import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "white"

    RowLayout{
        anchors.fill: parent
        PieChart{
            id: pieChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            PieSlice{
                color: "#FF9966"
                value: 10
            }
            PieSlice{
                color: "#66CCFF"
                value: 20
            }
            PieSlice{
                color: "#7A4A8D"
                value: 15
            }
            PieSlice{
                color: "#7575A3"
                value: 25
            }
        }
        //        ChartLegend{
        //            Layout.fillHeight: true
        //            source: pieChart
        //        }
    }
}

