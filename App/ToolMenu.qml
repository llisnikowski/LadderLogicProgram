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
    }
}
