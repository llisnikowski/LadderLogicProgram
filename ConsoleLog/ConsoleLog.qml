import QtQuick 2.15
import QtQuick.Controls 2.15


Item{
    Button{
        id: clearButton
        width: parent.width
        height: 30
        text: "Wyczyść"

        onClicked: {
            logTextArea.clear();
        }
    }

    Rectangle{
        color: "transparent"
        border.color: "darkgray"
        border.width: 1
        width: parent.width
        height: parent.height - clearButton.height
        y: clearButton.height

        Connections{
            target: parent
            ignoreUnknownSignals: true
            function onLogTextChanged(text){
                logTextArea.append(text)
            }
        }

        ScrollView{
            id:logScroll
            anchors.margins: 5
            anchors.fill: parent
            y: clearButton.height
            TextArea{
                id: logTextArea
                readOnly: true
                anchors.fill: parent
            }
        }
    }
}
