import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item{
    property var rootModel
    width: 64
    height: 20

    TextField{
        id: textField

        width: 64 * 0.7
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: TextInput.AlignVCenter;
        horizontalAlignment: TextEdit.AlignHCenter
        topPadding: 1;
        bottomPadding: 1;
        anchors.verticalCenterOffset: 5

        background: null
        clip: true
        font.pointSize: 8
        placeholderText: "..."
        color: rootModel.textIsValid ? "white" : "red"
        text: rootModel.textValue
        font.capitalization: Font.AllUppercase
        validator: rootModel.regExp

        onTextEdited: {
            if(textField.activeFocus){
                rootModel.textValue = textField.text
            }
        }
        onFocusChanged: {
            parent.onFocusChanged(textField.activeFocus);
        }
    }
}

