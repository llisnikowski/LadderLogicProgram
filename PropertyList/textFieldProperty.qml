import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    property var rootModel

    height: 60;

    spacing: 10
    padding: 10
    anchors.horizontalCenter: parent? parent.horizontalCenter : undefined

    Label{
        anchors.verticalCenter: parent.verticalCenter
        text: rootModel.propertyName+":"
    }

    TextField{
        id:textField;
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        text: rootModel.textValue
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
}
