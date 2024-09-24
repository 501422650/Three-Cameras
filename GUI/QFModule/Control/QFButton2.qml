import QtQuick

Item {
    id: root
    property string text: ""

    signal pressed()

    signal released()

    signal clicked()

    height: 85
    width: 343
    BorderImage {
        id: back
        source: "qrc:/QFModule/Image/Button/button2.png"
        anchors.fill: parent
        Text {
            color: "#ffffff"
            text: root.text
            font.pixelSize: 26
            font.family: "优设标题黑"
            font.bold: true
            anchors.centerIn: parent
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
        onPressed: {
            back.source = "qrc:/QFModule/Image/Button/button2_c.png"
            root.pressed()
        }
        onReleased: {
            back.source = "qrc:/QFModule/Image/Button/button2.png"
            root.released()
        }
    }
}