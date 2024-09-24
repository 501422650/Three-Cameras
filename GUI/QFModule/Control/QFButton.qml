import QtQuick 2.15
import QtQuick.Particles 2.0

Item {
    id: root
    property color color: "#0ff0ff"
    property string text: "Button"
    property bool hold: false
    property bool check: false


    signal pressed()

    signal released()

    signal clicked()

    clip: false
    BorderImage {
        id: background
        source: "qrc:/QFModule/Image/button.png"
        width: parent.width; height: parent.height
    }

    ParticleSystem {
        id: sys
        // 粒子发射速率
        property real particleEmitRate: 35
        // 粒子生命周期
        property real particleLifeSpan: 400
        // 发射器粒子颜色
        property string particleColor: "#ffffff"
        // 发射器粒子图片
        property string particleImage: "qrc:/QFModule/Image/light.png"
        x: 0
        y: -1
        width: parent.width
        height: 1
        ImageParticle {
            id: part
            system: sys
            color: sys.particleColor
            source: sys.particleImage
            entryEffect: ImageParticle.None
        }
        Emitter {
            id: emitter
            system: sys
            anchors.fill: parent
            emitRate: sys.particleEmitRate
            lifeSpan: sys.particleLifeSpan
            lifeSpanVariation: 100
            velocity: AngleDirection {
                angle: -90
                angleVariation: 0
                magnitude: 70
                magnitudeVariation: 20
            }
            size: 6 + 1
            sizeVariation: 3
            endSize: 1 + 1
            enabled: root.hold ? root.check : false
        }
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {
            button_text.color = "#d2872e"
            root.pressed()
        }
        onReleased: {
            if (root.hold) {
                button_text.color = "#ffffff"
                if (!root.check) {
                    button_text.color = "#d2872e"
                }
            } else {
                button_text.color = "#ffffff"
            }
            root.released()
        }
        onClicked: {
            root.check = !root.check
            root.clicked()
        }
        hoverEnabled: true
        onEntered: {
            emitter.enabled = true;
            background_d.visible = true
        }
        onExited: {
            if (!(root.hold && root.check)) {
                emitter.enabled = false;
                background_d.visible = false
            }
        }
    }

    Text {
        id: button_text
        text: parent.text
        color: root.hold ? root.check ? "#d2872e" : "#ffffff" : "#ffffff"
        font.pixelSize: parent.height / 3
        anchors.centerIn: parent
    }
    BorderImage {
        id: background_d
        visible: root.hold ? root.check : false
        source: "qrc:/QFModule/Image/button-d.png"
        width: parent.width; height: parent.height
        border.left: 1; border.top: 1
        border.right: 1; border.bottom: 1
    }

    function setCheck() {
        root.check = true
        emitter.enabled = true
        background_d.visible = true
        button_text.color = "#d2872e"
    }

    function setUnCheck() {
        root.check = false
        emitter.enabled = false
        background_d.visible = false
        button_text.color = "#ffffff"
    }
}
