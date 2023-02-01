import QtQuick 2.15

Item {
    property var rootModel

    width:200
    height: 100;

    anchors.horizontalCenter: parent? parent.horizontalCenter : undefined

    Image {
        anchors.fill: parent
        source: rootModel.url
    }
}
