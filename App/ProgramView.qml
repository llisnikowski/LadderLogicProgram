import QtQuick 2.12
import QtQuick.Controls 2.15

Item {
    MouseArea {
        anchors.fill: parent
        onClicked: {
            selectItem.resetItem();
            forceActiveFocus();
        }
    }

    ScrollView {
        anchors.fill: parent
        Flickable{
            contentHeight: networkList.height+300
            anchors.fill: parent
            Item{
                width: parent.width;
                height: networkList.height
                Component.onCompleted: {
                    networkList.parent = this;
                }
            }

        }
    }
}
