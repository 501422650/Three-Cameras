import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import ImageWindow
import QFModule
import QtQuick.VirtualKeyboard

Window {
    id: root
    title: qsTr("Hello World")
    visible: true
    visibility: "Maximized"
    flags: Qt.FramelessWindowHint
    property int targetID: 0;
    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: root.height
        width: root.width
        // scale: 0.5
        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: root.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
    Image {
        anchors.fill: parent
        source: "qrc:/QFModule/Image/Background/background2.png"
        QFTitle {
            id: title
            button1_text: "数据采集"
            button2_text: "数据分析"
            button3_text: "系统运行情况"
            button4_text: "系统设置"
            button5_text: "退出系统"
            onButton1_clicked: {
                win2.visible = false;
                win1.visible = true;
            }
            onButton2_clicked: {
                win1.visible = false;
                win2.visible = true;
            }
            onButton3_clicked: {
                var l = ""
                var u = 2
                var b = true
                var data = {
                    'path': l,
                    'unit': u,
                    'camera': (u * distanceInput.text) / 1000 + "m~" + ((u + 1) * distanceInput.text) / 1000 + "m",
                    'flag': b
                };
                model.append(data);
            }
            onButton4_clicked: {
                model.clear()
            }
            onButton5_clicked: {
                $Service.closeThread();
                root.close();
            }
        }
        Item {
            id: win1
            anchors.top: title.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            visible: true
            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                BorderImage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    source: "qrc:/QFModule/Image/Board/board1.png"
                    border.left: 85
                    border.top: 66
                    border.bottom: 85
                    border.right: 66
                    Image {
                        id: resultImg
                        anchors.fill: parent
                        anchors.margins: 20
                        source: ""
                    }
                }
                BorderImage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    source: "qrc:/QFModule/Image/Board/board1.png"
                    border.left: 85
                    border.top: 66
                    border.bottom: 85
                    border.right: 66
                    ColumnLayout {
                        id: colL1
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 0
                        ImageWindow {
                            id: cam1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    root.targetID = 0;
                                }
                            }
                        }
                        ImageWindow {
                            id: cam2
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    root.targetID = 1;
                                }
                            }
                        }
                        ImageWindow {
                            id: cam3
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    root.targetID = 2;
                                }
                            }
                        }
                    }
                    Item {
                        width: 3
                        anchors.bottom: colL1.bottom
                        anchors.left: colL1.right
                        anchors.top: colL1.top
                        Rectangle {
                            color: "#08fff4"
                            height: parent.height / 3
                            width: parent.width
                            y: targetID * height
                            Behavior on y {
                                NumberAnimation {
                                    duration: 300
                                    easing.type: Easing.OutCirc
                                }
                            }
                        }
                    }
                }
                BorderImage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    source: "qrc:/QFModule/Image/Board/board1.png"
                    border.left: 85
                    border.top: 66
                    border.bottom: 85
                    border.right: 66
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 30
                        spacing: 15
                        QFButton2 {
                            Layout.alignment: Qt.AlignHCenter
                            text: "连接相机"
                            onClicked: {
                                var infoArray = [];
                                infoArray.push(cam1, cam2, cam3);
                                $Service.startThread(infoArray);
                            }
                        }
                        QFButton2 {
                            Layout.alignment: Qt.AlignHCenter
                            text: "开始采集"
                            onClicked: {
                                if ($Service.ToggleTriggerMode()) {
                                    if (text === "开始采集") {
                                        text = "停止采集"
                                        model.clear()
                                        imgModel.clear()
                                    } else {
                                        text = "开始采集"
                                    }
                                }
                            }
                        }
                        QFFolderDialog {
                            Layout.alignment: Qt.AlignHCenter
                            width: 550
                            onFinished: (s) => {
                                $Service.SetSavePath(s)
                            }
                        }
                        BorderImage {
                            Layout.alignment: Qt.AlignHCenter
                            source: "qrc:/QFModule/Image/Background/background3.png"
                            Text {
                                x: 54
                                y: 9
                                text: "采集间距与时间"
                                color: "#ffffff"
                                font.pixelSize: 28
                                font.family: "优设标题黑"
                            }
                        }
                        QFInput {
                            id: distanceInput
                            name: "触发间距"
                            text: "500"
                            unit: "mm"
                            Layout.alignment: Qt.AlignHCenter
                            onEditFinished: {
                                console.log(text)
                                $Service.SetDistance(text);
                            }
                        }
                        QFInput {
                            name: "曝光时间"
                            text: "20000"
                            unit: "us"
                            Layout.alignment: Qt.AlignHCenter
                            onEditFinished: {
                                console.log(text)
                                inputPanel.active = false;
                                $Service.SetExposureTime(text)
                            }
                        }
                        BorderImage {
                            id: b1
                            Layout.alignment: Qt.AlignHCenter
                            source: "qrc:/QFModule/Image/Background/background3.png"
                            Text {
                                x: 54
                                y: 9
                                text: "灯光亮度调整区"
                                color: "#ffffff"
                                font.pixelSize: 28
                                font.family: "优设标题黑"
                            }
                        }
                        QFProgress {
                            Layout.alignment: Qt.AlignHCenter
                            onNumChanged: {
                                $Service.changeLight(num);
                            }
                        }
                        BorderImage {
                            Layout.alignment: Qt.AlignHCenter
                            source: "qrc:/QFModule/Image/Background/background3.png"
                            Text {
                                x: 54
                                y: 9
                                text: "镜头参数调整区"
                                color: "#ffffff"
                                font.pixelSize: 28
                                font.family: "优设标题黑"
                            }
                        }
                        GridLayout {
                            Layout.alignment: Qt.AlignHCenter
                            rows: 3
                            columns: 2
                            columnSpacing: 50
                            rowSpacing: 20
                            QFButton1 {
                                text: "聚焦+"
                                onPressed: {
                                    $Service.Len_Control(root.targetID, 1, 1);
                                }
                                onReleased: {
                                    $Service.Len_Control(root.targetID, 1, 3);
                                }
                            }
                            QFButton1 {
                                text: "聚焦-"
                                onPressed: {
                                    $Service.Len_Control(root.targetID, 1, 2);
                                }
                                onReleased: {
                                    $Service.Len_Control(root.targetID, 1, 3);
                                }
                            }
                            QFButton1 {
                                text: "变焦+"
                                onPressed: {
                                    $Service.Len_Control(root.targetID, 2, 1);
                                }
                                onReleased: {
                                    $Service.Len_Control(root.targetID, 2, 3);
                                }
                            }
                            QFButton1 {
                                text: "变焦-"
                                onPressed: {
                                    $Service.Len_Control(root.targetID, 2, 2);
                                }
                                onReleased: {
                                    $Service.Len_Control(root.targetID, 2, 3);
                                }
                            }
                            QFButton1 {
                                text: "光圈+"
                                onPressed: {
                                    $Service.Len_Control(root.targetID, 3, 1);
                                }
                                onReleased: {
                                    $Service.Len_Control(root.targetID, 3, 3);
                                }
                            }
                            QFButton1 {
                                text: "光圈-"
                                onPressed: {
                                    $Service.Len_Control(root.targetID, 3, 2);
                                }
                                onReleased: {
                                    $Service.Len_Control(root.targetID, 3, 3);
                                }
                            }
                        }

                    }
                }
            }
        }
        Item {
            id: win2
            anchors.top: title.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            visible: false
            RowLayout {
                anchors.fill: parent
                anchors.margins: 20

                BorderImage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    border.left: 401; border.top: 90
                    border.right: 90; border.bottom: 139
                    source: "qrc:/QFModule/Image/Background/background5.png"
                    ListView {
                        id: imgList
                        anchors.fill: parent
                        anchors.margins: 30
                        anchors.topMargin: 70
                        orientation: ListView.Horizontal
                        clip: true
                        ListModel {
                            id: imgModel
                        }
                        model: imgModel
                        delegate: Item {
                            height: imgList.height
                            width: 335
                            Image {
                                anchors.fill: parent
                                source: "file:///" + path
                            }
                        }
                        Connections {
                            target: $Service
                            onAddList: (l, u, b) => {
                                var data = {'path': l};
                                imgModel.append(data);
                                resultImg.source = "file:///" + l
                            }
                        }
                    }
                }
                BorderImage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    source: "qrc:/QFModule/Image/Board/board1.png"
                    border.left: 85
                    border.top: 66
                    border.bottom: 85
                    border.right: 66
                    QFListView {
                        anchors.fill: parent
                        anchors.margins: 50
                        model: model
                        ListModel {
                            id: model
                        }
                        Connections {
                            target: $Service
                            onAddList: (l, u, b) => {
                                var data = {
                                    'path': l,
                                    'unit': u,
                                    'camera': (u * distanceInput.text) / 1000 + "m~" + ((u + 1) * distanceInput.text) / 1000 + "m",
                                    'flag': b
                                };
                                model.append(data);
                            }
                        }
                    }
                }
            }
        }
    }


    function addList(unit, id, bad) {
        var data = {'unit': unit, 'camera': id, 'flag': bad};
        model.append();
    }

    FileDialog {
        id: fds1
        nameFilters: ["image files (*.jpg *.png *.bmp)"]
        title: "文件选择"
        onAccepted: {

        }
        onRejected: {
            console.log("Canceled")
        }
    }
    QFDialog {
        id: dialog
        anchors.centerIn: parent
    }
    Component.onCompleted: {
        root.showFullScreen()

    }
}
