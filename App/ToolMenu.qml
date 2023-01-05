import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

Item {
    Label {
        text: "PLC"
        anchors.centerIn: parent
    }
    Label {
        text: "version 0.8"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
    }
    RowLayout {
        FileButton{
        }

        ToolButton {
            id: connectButton
//            text: serialPort.deviceConnected ? "\u2666" : "\u2662"
            text: serialPort.deviceConnected ? "Połącz" : "Rozłącz"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.pixelSize: Qt.application.font.pixelSize * 1

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
            id: verifyButton
            text: "Sprawdź"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
                interfaceButtons.verify();
            }
        }
        ToolButton {
            id: uploadButton
            text: "Prześlij"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
                interfaceButtons.upload();
            }
        }
        ToolButton {
            id: plcModeButton
            text: " Start "
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
                interfaceButtons.plcMode();
            }
        }
        ToolButton {
            id: setTimeButton
            text: "Ustaw czas"
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
                interfaceButtons.setCurrentTime();
            }
        }
    }
}
