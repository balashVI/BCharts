import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "white"

    RowLayout{
        anchors.fill: parent
        PolarAreaChart{
            id: polarAreaChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            polarAreas: [
                PolarArea{
                    color: "#D47E6A"
                    value: 20
                },PolarArea{
                    color: "#66CCFF"
                    value: 5
                },PolarArea{
                    color: "#7A4A8D"
                    value: 18
                },PolarArea{
                    color: "#4C996B"
                    value: 25
                }
            ]
        }
        ChartLegend{
            Layout.fillHeight: true
            source: polarAreaChart
        }
    }
}

