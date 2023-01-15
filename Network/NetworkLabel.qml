import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Rectangle{
    property var network

    id:label
    width: network.width
    color: "Gray";
    height: 24

    MouseArea{
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: {
            if(!labelContext.visible)
                labelContext.open();
            else
                labelContext.close();
        }
    }

    Menu {
        id: labelContext
        x: mouseArea.mouseX
        y: mouseArea.mouseY

        MenuItem {
            height: 30
            font.pixelSize: 12
            text: "Przenieś w górę"
            onClicked: {
            }
        }
        MenuItem {
            height: 30
            font.pixelSize: 12
            text: "Przenieś w dół"
            onClicked: {
            }
        }
        MenuItem {
            height: 30
            font.pixelSize: 12
            text: "Wstaw poniżej"
            onClicked: {
            }
        }
        MenuItem {
            height: 30
            font.pixelSize: 12
            text: "Wstaw powyżej"
            onClicked: {
            }
        }
        MenuItem {
            height: 30
            font.pixelSize: 12
            text: "Usuń Networka"
            onClicked: {
                network.triggerDeletion();
            }
        }

    }

    Label {
        id: networkText
        text: "Network " + network.nr;
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 2;
    }
    TextField{
        id: description
        anchors.verticalCenter: label.verticalCenter;
        anchors.left: networkText.right;
        anchors.right: label.right;
        anchors.leftMargin: 10
        verticalAlignment: TextInput.AlignVCenter;
        font.pointSize: 8
        anchors.verticalCenterOffset: 4
        anchors.rightMargin: 0
        placeholderText: "Opis.."
        background: null
        text: network.desctiption
        onTextEdited: {
            if(description.activeFocus){
                network.desctiption = description.text
            }
        }
    }
}
