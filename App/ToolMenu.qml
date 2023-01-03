import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    Label {
        text: "PLC"
        anchors.centerIn: parent
    }
    Label {
        text: "version 0.7"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
    }
    RowLayout {
        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
        }
        ToolButton {
            id: connectButton
            text: serialPort.deviceConnected ? "\u2666" : "\u2662"
            font.pixelSize: Qt.application.font.pixelSize * 1.6

            property ApplicationWindow connectWindow;
            onClicked: {
                if(!connectWindow){
                    var component = Qt.createComponent("SerialPortWindow.qml")
                    connectWindow = component.createObject(window)
                    connectWindow.show()
                    connectWindow.closing.connect(closeConnectWindow)
                }
            }
            function closeConnectWindow(){
                connectWindow = null
            }
        }
        ToolButton {
            id: checkButton
            text: "\u2713" //"\u27A5"
            font.pixelSize: Qt.application.font.pixelSize * 1.6

            onClicked: {
                codeGenerator.verify();
            }
        }
    }
}
