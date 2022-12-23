import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle{
    color: "transparent"
    border.color: "darkgray"
    border.width: 1

    Connections{
        target: consoleLog
        ignoreUnknownSignals: true
        function onLogTextChanged(text){
            logTextArea.append(text)
        }
    }

    ScrollView{
        id:logScroll
        anchors.margins: 5
        anchors.fill: parent
        TextArea{
            id: logTextArea
            readOnly: true
            anchors.fill: parent
        }
    }
}
