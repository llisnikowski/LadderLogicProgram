import QtQuick 2.15
import QtQuick.Controls 2.15


Row {
    property var rootModel;

    height: 60;
    spacing: 10
    padding: 10
    anchors.horizontalCenter: parent? parent.horizontalCenter : undefined

    Label{
        anchors.verticalCenter: parent.verticalCenter
        text: rootModel.propertyName + ":"
    }

    ComboBox{
        id:comboBox
        anchors.verticalCenter: parent.verticalCenter
        width: 128
        height: 50
        font.pixelSize: 18
        model: rootModel.model
        currentIndex: rootModel.value;

        onActivated: {
            rootModel.value = currentIndex
        }
    }
}
