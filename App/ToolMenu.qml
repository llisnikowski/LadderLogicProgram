import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

Item {
    Label {
        text: "PLC"
        anchors.centerIn: parent
    }
    RowLayout {
        FileButton{
        }

        ToolButton {
            id: connectButton
            text: serialPort.deviceConnected ? "Rozłącz" : "Połącz"
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
            onClicked: {
                interfaceButtons.verify();
            }
        }
        ToolButton {
            id: uploadButton
            text: "Wgraj"
            onClicked: {
                interfaceButtons.upload();
            }
        }
//        ToolButton {
//            id: plcModeButton
//            text: " Start "
//            onClicked: {
//                interfaceButtons.plcMode();
//            }
//        }
        ToolButton {
            id: setTimeButton
            text: "Ustaw czas"
            onClicked: {
                interfaceButtons.setCurrentTime();
            }
        }
        ToolButton {
            id: info
            text: " Info "
            property ApplicationWindow connectWindow;
            onClicked: {
                if(!connectWindow){
                    var component = Qt.createComponent("Info.qml")
                    connectWindow = component.createObject(window)
                    connectWindow.show()
                    connectWindow.closing.connect(closeConnectWindow)
                }
            }
            function closeConnectWindow(){
                connectWindow = null
            }
        }
    }
}
