import QtQuick
import QtQuick.Dialogs

Item {
    id: root
    property url fileUrl

    signal pressed()

    signal released()

    signal clicked()

    signal chooseFinish()

    Image {
        id: bg
        source: "qrc:/QFModule/Image/upload.png"
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
            onPressed: {
                root.pressed()
            }
            onReleased: {
                root.released()
            }
            onClicked: {
                fds.open()
                root.clicked()
            }
            hoverEnabled: true
            onEntered: {
                bg.source = "qrc:/QFModule/Image/upload-d.png"
            }
            onExited: {
                bg.source = "qrc:/QFModule/Image/upload.png"
            }
        }
    }
    FileDialog {
        id: fds
        title: "选择文件"
        nameFilters: ["image files (*.jpg *.png)"]
        onAccepted: {
            root.fileUrl = fds.currentFile
            root.chooseFinish()
        }
        onRejected: {
            console.log("Canceled");
        }
    }
}