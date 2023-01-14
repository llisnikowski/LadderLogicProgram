import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property var rootModel
    anchors.fill: parent

    MouseArea {
        anchors.fill: parent
        onClicked: {
            forceActiveFocus();
        }
    }

    Column{
        id: container;
        anchors.fill: parent
    }

    Connections {
        target: rootModel
        function onAddPropertyItem(item) {
            item.parent = container;
        }
    }


}
