import QtQuick 2.12
import QtQuick.Controls 2.15

Item{
    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        width: 64
        height: parent.height
        spacing: 8

        Component.onCompleted: {
            ldSymbolsBar.setNewParentItem(this);
        }
    }
}
