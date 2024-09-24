import QtQuick
import QtQuick.Dialogs

Item {
    id: root
    height: 35

    signal finished(s: string)

    BorderImage {
        id: button
        source: "qrc:/QFModule/Image/TextInput/textinput3.png"
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: 137
        Text {
            font.pixelSize: 18
            font.family: "优设标题黑"
            color: "#ffffff"
            anchors.centerIn: parent
            text: "选择文件夹"
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                button.source = "qrc:/QFModule/Image/TextInput/textinput4.png"
            }
            onReleased: {
                button.source = "qrc:/QFModule/Image/TextInput/textinput3.png"
            }
            onClicked: {
                folderDialog.open()
            }
        }
    }
    BorderImage {
        id: background
        source: "qrc:/QFModule/Image/TextInput/textinput2.png"
        anchors.left: parent.left
        anchors.right: button.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        clip: true
        TextInput {
            id: cur
            text: "未选择文件夹"
            font.pixelSize: 18
            font.family: "优设标题黑"
            color: "#ffffff"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
        }
    }
    FolderDialog {
        id: folderDialog
        currentFolder: ""
        selectedFolder: ""
        onAccepted: {
            var path = currentFolder.toString();
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/, "");
            cur.text = path
            cur.font.family = ""
            root.finished(path)
        }
    }
}