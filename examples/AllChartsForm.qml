import QtQuick 2.4
import QtQuick.Layouts 1.1

Rectangle {

    anchors.fill: parent
    GridLayout{
            anchors.fill: parent
            anchors.margins: 5
            columns: 3
            LineChartForm{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            BarChartForm{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            PieChartForm{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            XYChartForm{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            BubbleChartForm{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            PolarAreaChartForm{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
}

