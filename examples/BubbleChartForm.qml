import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Layouts 1.1

Rectangle {
    RowLayout{
        anchors.fill: parent
        BubbleChart {
            id: bubleChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            maxBubbleRadius: 30
            series: [
                BubbleSeries {
                    name: "First"
                    data: [
                        Bubble {
                            x: 0
                            y: 0
                            value: 1
                        },
                        Bubble {
                            x: 1
                            y: 1
                            value: 2
                        },
                        Bubble {
                            x: 2
                            y: 2
                            value: 3
                        },
                        Bubble {
                            x: 3
                            y: 3
                            value: 4
                        },
                        Bubble {
                            x: 4
                            y: 4
                            value: 5
                        }
                    ]
                    color: "#aa7575A3"
                    strokePen.color: "#5C5C8A"
                },
                BubbleSeries {
                    name: "Second"
                    data: [
                        Bubble {
                            x: 0
                            y: 5
                            value: 8
                        },
                        Bubble {
                            x: 1
                            y: 4
                            value: 7
                        },
                        Bubble {
                            x: 2
                            y: 3
                            value: 6
                        },
                        Bubble {
                            x: 3
                            y: 4
                            value: 2
                        }
                    ]
                    color: "#aa4Ca8d6"
                    strokePen.color: "#66CCFF"
                }
            ]
        }
        ChartLegend{
            Layout.fillHeight: true
            source: bubleChart
        }
    }
}
