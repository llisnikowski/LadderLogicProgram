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
        text: rootModel.propertyName+":"
    }

    TextField{
        id:textField;
        anchors.verticalCenter: parent.verticalCenter
        text: rootModel.textValue;
        placeholderText: rootModel.placeholder
        color:  rootModel.textIsValid ? "white" : "red"
        selectByMouse: true
        clip: true

        onTextEdited: {
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
