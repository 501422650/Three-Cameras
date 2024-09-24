import QtQuick
import QtQuick.Controls

Item {
    id: root
    property string text: ""

    signal editFinished()

    BorderImage {
        source: "qrc:/QFModule/Image/textInput_bg.png"
        anchors.fill: parent
        border.bottom: 7
        border.left: 7
        border.right: 7
        border.top: 7
    }
    TextInput {
        id: t
        anchors.fill: parent
        font.pixelSize: parent.height * 0.6
        verticalAlignment: Text.AlignVCenter
        anchors.margins: 3
        anchors.leftMargin: 6
        color: "#ffffff"
        text: root.text
        onEditingFinished: {
            root.text = t.text
            root.editFinished();
        }
    }
}