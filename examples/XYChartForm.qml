import QtQuick 2.4
import QtQuick.Layouts 1.1
import BVI.Charts 1.0

Rectangle {
    color: "white"

    RowLayout{
        anchors.fill: parent
        XYChart {
            id: xyChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            series: [
                XYSeries {
                    id: chartSeries
                    data: [
                        ChartPoint {
                            x: 0
                            y: 0
                        },
                        ChartPoint {
                            x: 1
                            y: 2
                        },
                        ChartPoint {
                            x: 3
                            y: 1
                        },
                        ChartPoint {
                            x: 1
                            y: 5
                        },
                        ChartPoint {
                            x: 1
                            y: 3
                        }
                    ]
                    color: "#aa7575A3"
                    strokePen.color: "#5C5C8A"
                },
                XYSeries {
                    data: [
                        ChartPoint {
                            x: 5
                            y: 5
                        },
                        ChartPoint {
                            x: 3
                            y: 2
                        },
                        ChartPoint {
                            x: 3
                            y: 4
                        },
                        ChartPoint {
                            x: 1
                            y: 1
                        }
                    ]
                    color: "#4Ca8d6"
                    strokePen.color: "#66CCFF"
                }
            ]
        }
        ChartLegend{
            Layout.fillHeight: true
            source: xyChart
        }
    }
}
