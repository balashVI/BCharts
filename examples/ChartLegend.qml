import QtQuick 2.3

Item {
    id: root
    width: 100
    clip: true

    property QtObject source

    ListView{
        id: list
        anchors.fill: parent
        spacing: 5

        delegate: Item{
            height: 30
            width: parent.width
            Rectangle{
                id: ico
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 3
                width: height
                color: modelData.color
                border.color: modelData.strokeColor ? modelData.strokeColor : ""
                border.width: modelData.strokeWidth ? modelData.strokeWidth : 0
                radius: 8
            }

            Text{
                text: modelData.name
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: ico.right
                anchors.margins: 5
                renderType: Text.NativeRendering
            }
        }
    }
    Connections{
        target: source
        onLegendChanged: list.model = source.generateLegend()
    }

    Component.onCompleted: {
        if(source)
            list.model = source.generateLegend()
    }
}
