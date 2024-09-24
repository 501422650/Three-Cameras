import QtQuick

ListView {
    id: root
    headerPositioning: ListView.OverlayHeader;
    clip: true;
    signal currented(s: string)

    header: BorderImage {
        width: parent.width
        height: 30
        z: 99
        source: "qrc:/QFModule/Image/ListView/head.png"

        Text {
            text: "单元号"
            color: "#ffffff"
            font.pixelSize: 18
            font.family: "优设标题黑"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
        }
        Text {
            text: "采集区间"
            color: "#ffffff"
            font.pixelSize: 18
            font.family: "优设标题黑"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "识别结果"
            color: "#ffffff"
            font.pixelSize: 18
            font.family: "优设标题黑"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 30
        }
        MouseArea {
            anchors.fill: parent;
            onPressed: {
                mouse.accepted = true;
            }
        }
    }
    delegate: BorderImage {
        id: item
        width: root.width
        property string background: index % 2 ? "qrc:/QFModule/Image/ListView/item1.png" : "qrc:/QFModule/Image/ListView/item2.png"
        height: 30
        source: item.background
        Text {
            font.pixelSize: 18
            font.family: "优设标题黑"
            color: "#ffffff"
            text: unit
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
        }
        Text {
            font.pixelSize: 18
            font.family: "优设标题黑"
            color: "#ffffff"
            text: camera
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Image {
            source: flag ? "qrc:/QFModule/Image/ListView/ok.png" : "qrc:/QFModule/Image/ListView/error.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 22
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            // onPressed: {
            //     item.source = "qrc:/QFModule/Image/ListView/item_clicked.png"
            // }
            // onReleased: {
            //     item.source = item.background
            // }
            onEntered: {
                item.source = "qrc:/QFModule/Image/ListView/item_clicked.png"
            }
            onExited: {
                item.source = item.background
            }
            onDoubleClicked: {
                root.currented(path)
                console.log(path)
            }
        }
    }
}