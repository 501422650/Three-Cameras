import QtQuick

Image {
    id: root
    source: "qrc:/QFModule/Image/Background/background4.png"
    visible: false
    MouseArea {
        x: 1085
        y: 35
        width: 45
        height: 45
        onClicked: {
            root.close();
        }
    }
    Image {
        id: img
        source: ""
        width: 1052
        height: 879
        x: 74
        y: 100
    }

    function open(s) {
        img.source = "file:///" + s;
        console.log(s)
        root.visible = true;
    }

    function close() {
        root.visible = false;
    }
}