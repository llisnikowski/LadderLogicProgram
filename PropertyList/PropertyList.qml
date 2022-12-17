import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
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
//        Label{
//            padding: 5
////            anchors.horizontalCenter: parent.horizontalCenter
////            text: selectedComponent.mainLabel
//            font.pixelSize: 20;
//        }
    }

    Connections {
        target: parent
        function onAddPropertyItem(item) {
            item.parent = container;
        }
    }


}
