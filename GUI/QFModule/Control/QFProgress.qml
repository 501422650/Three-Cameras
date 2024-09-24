import QtQuick 2.15
import QtQuick.Layouts

Item {
    id: root
    property real num: 0;
    width: 500
    height: 25
    Image {
        property bool t: false;
        id: background
        source: "qrc:/QFModule/Image/Progress/progress1.png"
        Image {
            id: button
            x: 0
            source: "qrc:/QFModule/Image/Progress/progress2.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 2
            transform: Translate {
                x: -39
            }
            Behavior on x {
                NumberAnimation {
                    duration: 300
                    easing.type: Easing.OutCirc
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onReleased: {
                background.t = false;
                if (mouseX > 0 && mouseX < parent.width) {
                    button.x = mouseX
                    n.text = (mouseX * 100 / parent.width).toFixed(1) + "%";
                } else if (mouseX < 0) {
                    button.x = 0;
                    n.text = 0 + "%";
                } else {
                    button.x = parent.width
                    n.text = 100 + "%";
                }
            }
            onPressed: {
                background.t = true;
            }
            onPositionChanged: {
                if (background.t && mouseX > 0 && mouseX < parent.width) {
                    button.x = mouseX
                    n.text = (mouseX * 100 / parent.width).toFixed(1) + "%";
                    root.num = mouseX * 100 / parent.width;
                } else if (background.t && mouseX < 0) {
                    button.x = 0;
                    n.text = 0 + "%";
                    root.num = 0;
                } else {
                    button.x = parent.width
                    n.text = 100 + "%";
                    root.num = 100;
                }
            }
        }
    }
    Text {
        id: n
        text: "0%"
        font.pixelSize: 26
        font.family: "优设标题黑"
        // font.bold: true
        color: "#ffffff"
        anchors.verticalCenter: background.verticalCenter
        anchors.left: background.right
        anchors.leftMargin: 20
    }
    Component.onCompleted: {
        console.log(root.width)
    }
}
