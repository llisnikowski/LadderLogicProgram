import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Rectangle{
    property var network

    id:label
    width: network.width*0.8
    color: "Gray";
    height: 24

    Label {
        id: networkText
        text: "Network " + network.nr;
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 2;
    }
    TextField{
        anchors.verticalCenter: label.verticalCenter;
        anchors.left: networkText.right;
        anchors.right: label.right;
        anchors.leftMargin: 10
        verticalAlignment: TextInput.AlignVCenter;
        font.pointSize: 8
        anchors.verticalCenterOffset: 4
        anchors.rightMargin: 0
        placeholderText: "Comment"
        background: null
    }
}
