import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

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
        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
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
            id: checkButton
            text: "Sprawdź"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
                consoleLog.addToLogs("Sprawdzanie programu...");
                if(codeGenerator.verify()){
                    consoleLog.addToLogs("Program poprawny");
                }
                else{
                    consoleLog.addToLogs("Program niepoprawny");
                }
            }
        }
        ToolButton {
            id: uploadButton
            text: "Prześlij"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
                if(codeGenerator.verify()){
                    consoleLog.addToLogs("Wysyłanie programu...");
                    serialPort.send(codeGenerator.code);
                }
            }
        }
        ToolButton {
            id: plcModeButton
            text: " Start "
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
            }
        }
        ToolButton {
            id: setTimeButton
            text: "Ustaw czas"
            font.pixelSize: Qt.application.font.pixelSize * 1

            onClicked: {
            }
        }
    }
}
