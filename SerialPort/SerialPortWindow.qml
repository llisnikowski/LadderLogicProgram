import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id:drawer
    //anchors.fill: parent
    width: 600
    height: 150

    Column{
        anchors.centerIn: parent
        spacing: 4;
        padding: 4;
        RowLayout{
            spacing: 4;
            Button {
                text: "Szukaj"
                onClicked: serialPort.searchDevices();
            }
            ComboBox{
                id: comboBox
                implicitWidth: 300
                font.pixelSize: 14;
                model: serialPort.foundDevices
                onActivated: serialPort.selectDevice = currentIndex
            }
            Button {
                text: "Połącz"
                onClicked: serialPort.connect();
            }
            Button {
                text: "Rozłącz"
                onClicked: serialPort.disconnect();
            }
        }

    }



}
