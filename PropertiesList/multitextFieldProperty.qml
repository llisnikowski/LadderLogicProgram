import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    property var rootModel

    height: 50*4+10;

    spacing: 10
    padding: 10
    anchors.horizontalCenter: parent? parent.horizontalCenter : undefined

    Label{
        y: 20
        text: rootModel.propertyName+":"
    }

    Column{
        Repeater{
            model: rootModel.numberOfTexts
            TextField{
                property int number: index
                id:textField;
                width: 300
                height: 50
                horizontalAlignment: TextInput.AlignHCenter
                text: rootModel.textsList[index]
                placeholderText: "..."
                color: "white"
                selectByMouse: true
                clip: true

                onTextChanged: {
                    if(textField.activeFocus){
                        rootModel.textsList[index] = textField.text
                    }
                }
            }
        }
    }
}
