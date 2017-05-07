import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "#454754"

    RowLayout{
        anchors.fill: parent
        PieChart{
            id: pieChart
            Layout.fillHeight: true
            Layout.fillWidth: true

            PieSlice{
                color: "#9688f7"
                value: 2
            }
            PieSlice{
                id: pie
                color: "#57dce5"
                value: 1.2
            }
            PieSlice{
                color: "#b659b4"
                value: 1.5
            }
            PieSlice{
                color: "#3bbcfc"
                value: 3
            }
            PieSlice{
                color: "#6597a2"
                value: 1
            }
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            pie.value += 5;
            pie.color = "red";
        }
    }
}

