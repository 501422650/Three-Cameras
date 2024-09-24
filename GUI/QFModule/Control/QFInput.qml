import QtQuick
import QtQuick.Layouts

Image {
    id: root
    source: "qrc:/QFModule/Image/TextInput/textinput1.png"
    width: 513
    height: 50
    property string name: ""
    property string text: ""
    property string unit: ""

    signal editFinished()

    Text {
        text: root.name
        font.pixelSize: 18
        font.family: "优设标题黑"
        color: "#ffffff"
        x: 14
        y: 11
    }
    Text {
        id: t
        x: 350
        y: 8
        font.pixelSize: 24
        font.family: "优设标题黑"
        color: "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        text: root.text
        // onEditingFinished: {
        //     root.text = t.text
        //     root.editFinished();
        // }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                keyboard.visible = !keyboard.visible
                if (keyboard.visible) {
                    root.z = 99
                } else {
                    root.z = 5

                }
            }
        }
    }
    Text {
        text: root.unit
        font.pixelSize: 24
        font.family: "优设标题黑"
        color: "#ffffff"
        x: 483
        y: 8
    }
    Image {
        id: keyboard
        source: "qrc:/QFModule/Image/TextInput/textinput7.png"
        anchors.top: parent.bottom
        visible: false
        z: 99

        Image {
            x: 0
            y: -7
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "1"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "1"
                }
            }
        }
        Image {
            x: 116
            y: -7
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "2"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "2"
                }
            }
        }
        Image {
            x: 232
            y: -7
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "3"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "3"
                }
            }
        }
        Image {
            x: 0
            y: 68
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "4"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "4"
                }
            }
        }
        Image {
            x: 116
            y: 68
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "5"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "5"
                }
            }
        }
        Image {
            x: 232
            y: 68
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "6"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "6"
                }
            }
        }
        Image {
            x: 0
            y: 143
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "7"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "7"
                }
            }
        }
        Image {
            x: 116
            y: 143
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "8"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "8"
                }
            }
        }
        Image {
            x: 232
            y: 143
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "9"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "9"
                }
            }
        }
        Image {
            x: 0
            y: 218
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "Back"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text = root.text.slice(0, -1)
                }
            }
        }
        Image {
            x: 116
            y: 218
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "0"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    root.text += "0"
                }
            }
        }
        Image {
            x: 232
            y: 218
            source: "qrc:/QFModule/Image/TextInput/textinput6.png"
            Text {
                text: "确认"
                font.pixelSize: 32
                font.family: "优设标题黑"
                color: "#ffffff"
                anchors.centerIn: parent
            }
            MouseArea {
                width: 103
                height: 62
                anchors.centerIn: parent
                onPressed: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput5.png"
                }
                onReleased: {
                    parent.source = "qrc:/QFModule/Image/TextInput/textinput6.png"
                }
                onClicked: {
                    keyboard.visible = !keyboard.visible
                    if (keyboard.visible) {
                        root.z = 99
                    } else {
                        root.z = 5
                    }
                    root.editFinished()
                }
            }
        }
    }
}