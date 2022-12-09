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

    Component.onCompleted: {
        networkList.joinToParent(this);
    }
}
