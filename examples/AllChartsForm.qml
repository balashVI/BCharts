import QtQuick 2.4
import QtQuick.Layouts 1.1

Rectangle {
    color: "#454754"

    anchors.fill: parent
    GridLayout{
        anchors.fill: parent
        anchors.margins: 5
        columns: 3
        PieChartForm{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

