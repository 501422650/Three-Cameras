import QtQuick
import QtQuick.Dialogs
import ImageItem

Item {
    id: root
    property url source
    clip: true
    ImageItem {
        id: img
        anchors.fill: parent
        anchors.centerIn: parent
        onImageChanged: {
            console.log("changed");
        }
    }


    function loadImage(url) {
        img.anchors.centerIn = root
        img.loadImage(url);
    }

    function clearImage() {
        img.clearImage();
    }

    function setImage(a) {
        img.image = a;
    }

    function setAddFlag(a) {
        img.addFlag = a;
    }
}