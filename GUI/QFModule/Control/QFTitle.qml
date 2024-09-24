import QtQuick

Rectangle {
    property string button1_text: ""
    property string button2_text: ""
    property string button3_text: ""
    property string button4_text: ""
    property string button5_text: ""

    signal button1_clicked()

    signal button2_clicked()

    signal button3_clicked()

    signal button4_clicked()

    signal button5_clicked()

    id: root
    width: 1920
    height: 120
    color: "transparent"
    Image {
        anchors.fill: parent
        source: "qrc:/QFModule/Image/Title/title_background.png"
        Text {
            y: 21
            text: "表观检测数据采集系统"
            color: "#ffffff"
            font.family: "庞门正道标题体免费版"
            font.pixelSize: 34
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle {
            x: 1723
            y: 25
            width: 116
            height: 38
            color: "transparent"
            Text {
                id: date
                color: "#ffffff"
                font.family: "Acens"
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: time
                y: 11
                color: "#ffffff"
                // font.family: "Acens"
                font.pixelSize: 24
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Timer {
                id: nowTimer;
                interval: 1000;
                running: true;
                repeat: true
                onTriggered: {
                    date.text = getCurDate()//此处即是让时间显示到文本中去
                    time.text = getCurTime();
                }
            }
        }

        Image {
            id: button1
            width: 243
            height: 50
            x: 14
            y: 23
            source: "qrc:/QFModule/Image/Title/title_button1_c.png"
            Text {
                text: root.button1_text
                color: "#ffffff"
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
            }
            MouseArea {
                width: 174
                height: 34
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
                onClicked: {
                    button1_clicked();
                }
                onPressed: {
                    button1.source = "qrc:/QFModule/Image/Title/title_button1_c.png"
                    button2.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button3.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button4.source = "qrc:/QFModule/Image/Title/title_button2.png"
                }
            }
        }
        Image {
            id: button2
            width: 243
            height: 50
            x: 235
            y: 23
            source: "qrc:/QFModule/Image/Title/title_button1.png"
            Text {
                text: root.button2_text
                color: "#ffffff"
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
            }
            MouseArea {
                width: 174
                height: 34
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
                onClicked: {
                    button2_clicked();
                }
                onPressed: {
                    button1.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button2.source = "qrc:/QFModule/Image/Title/title_button1_c.png"
                    button3.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button4.source = "qrc:/QFModule/Image/Title/title_button2.png"
                }
            }
        }
        Image {
            id: button3
            width: 243
            height: 50
            x: 456
            y: 23
            source: "qrc:/QFModule/Image/Title/title_button1.png"
            Text {
                text: root.button3_text
                color: "#ffffff"
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
            }
            MouseArea {
                width: 174
                height: 34
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
                onClicked: {
                    button3_clicked();
                }
                onPressed: {
                    button1.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button2.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button3.source = "qrc:/QFModule/Image/Title/title_button1_c.png"
                    button4.source = "qrc:/QFModule/Image/Title/title_button2.png"
                }
            }
        }
        Image {
            id: button4
            width: 243
            height: 50
            x: 1234
            y: 23
            source: "qrc:/QFModule/Image/Title/title_button2.png"
            Text {
                text: root.button4_text
                color: "#ffffff"
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
            }
            MouseArea {
                width: 174
                height: 34
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
                onClicked: {
                    button4_clicked();
                }
                onPressed: {
                    button1.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button2.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button3.source = "qrc:/QFModule/Image/Title/title_button1.png"
                    button4.source = "qrc:/QFModule/Image/Title/title_button2_c.png"
                }
            }
        }
        Image {
            id: button5
            width: 243
            height: 50
            x: 1451
            y: 23
            source: "qrc:/QFModule/Image/Title/title_button2.png"
            Text {
                text: root.button5_text
                color: "#ffffff"
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
            }
            MouseArea {
                width: 174
                height: 34
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -5
                onClicked: {
                    button5_clicked();
                }
                onPressed: {
                    button5.source = "qrc:/QFModule/Image/Title/title_button2_c.png"
                }
                onReleased: {
                    button5.source = "qrc:/QFModule/Image/Title/title_button2.png"
                }
            }
        }
    }
    Component.onCompleted: {
        date.text = getCurDate()//此处即是让时间显示到文本中去
        time.text = getCurTime();
    }

    function getCurDate() {
        var d = new Date();
        var years = d.getFullYear();
        var month = add_zero(d.getMonth() + 1);
        var days = add_zero(d.getDate());
        return years + "/" + month + "/" + days;
    }

    function getCurTime() {
        var d = new Date();
        var hours = add_zero(d.getHours());
        var minutes = add_zero(d.getMinutes());
        var seconds = add_zero(d.getSeconds());
        return hours + ":" + minutes + ":" + seconds;
    }

    function add_zero(temp) {
        if (temp < 10)
            return "0" + temp;
        else
            return temp;
    }
}