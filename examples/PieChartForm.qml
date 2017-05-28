import QtQuick 2.5
import QtQuick.Layouts 1.1
import BVI.Charts 2.0

Rectangle {

    RowLayout{
        anchors.fill: parent

        PieChart{
            id: pieChart
            Layout.fillHeight: true
            Layout.fillWidth: true

            PieSlice{
                name: "First"
                color: "#FF9966"
                value: 10
            }
            PieSlice{
                name: "Second"
                color: "#66CCFF"
                value: 20
            }
            PieSlice{
                name: "Third"
                color: "#3C895B"
                value: 15
            }
            PieSlice{
                name: "Fourth"
                color: "#7575A3"
                value: 25
            }
        }

        ChartLegend{
            Layout.fillHeight: true
            width: 150
            source: pieChart
        }
    }
}

