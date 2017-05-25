import QtQuick 2.4
import BVI.Charts 2.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "white"

    RowLayout{
        anchors.fill: parent
        PolarAreaChart{
            id: polarAreaChart
            Layout.fillHeight: true
            Layout.fillWidth: true

            PolarArea{
                name: "First"
                color: "#9688f7"
                value: 2
            }
            PolarArea{
                name: "Second"
                color: "#57dce5"
                value: 1.2
            }
            PolarArea{
                name: "Third"
                color: "#b659b4"
                value: 1.5
            }
            PolarArea{
                name: "Fourth"
                color: "#3bbcfc"
                value: 3
            }
            PolarArea{
                name: "Fifth"
                color: "#6597a2"
                value: 1
            }
        }
        ChartLegend{
            Layout.fillHeight: true
            source: polarAreaChart
        }
    }
}

