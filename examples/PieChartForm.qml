import QtQuick 2.5
import QtQuick.Layouts 1.1
import BVI.Charts 2.0

Rectangle {
    color: "#454754"

    RowLayout{
        anchors.fill: parent

        PieChart{
            id: pieChart
            Layout.fillHeight: true
            Layout.fillWidth: true

            PieSlice{
                name: "First"
                color: "#9688f7"
                value: 2
            }
            PieSlice{
                name: "Second"
                color: "#57dce5"
                value: 1.2
            }
            PieSlice{
                name: "Third"
                color: "#b659b4"
                value: 1.5
            }
            PieSlice{
                name: "Fourth"
                color: "#3bbcfc"
                value: 3
            }
            PieSlice{
                name: "Fifth"
                color: "#6597a2"
                value: 1
            }
        }

        ChartLegend{
            Layout.fillHeight: true
            width: 150
            source: pieChart
        }
    }
}

