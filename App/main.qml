import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("PLC")

    header: ToolBar {
        id: toolBar
        ToolMenu {
            anchors.fill: parent
        }
    }

//    Content{
//        anchors.fill: parent
//    }

    Image {
        source: "img/timer/timer1.png"
    }
}

