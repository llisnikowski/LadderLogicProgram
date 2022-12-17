import QtQuick 2.15
import QtQuick.Controls 2.15


Row {
    property var rootModel;

    height: 60;
    spacing: 10
    padding: 10
    anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined

    Label{
        anchors.verticalCenter: parent.verticalCenter
        text: rootModel.name+":"
    }

    TextField{
        id:textField;
        anchors.verticalCenter: parent.verticalCenter
        text: rootModel.textValue;
        placeholderText: "..."
        color: "white"
        selectByMouse: true
        clip: true

        onTextChanged: {
            if(textField.activeFocus){
                rootModel.textValue = textField.text
            }
        }
    }

    ComboBox{
        id:comboBox
        anchors.verticalCenter: parent.verticalCenter
        width:96;
        height:50;
        font.pixelSize: 14
        model: rootModel.model
        currentIndex: rootModel.units;

        onActivated: {
            rootModel.units = currentIndex
        }
        indicator { //strzałka
            width: 16;
        }
    }
}
