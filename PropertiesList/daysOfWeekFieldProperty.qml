import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    property var rootModel;

    height: 60;
    spacing: 10
    anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined

    Label{
        anchors.verticalCenter: parent.verticalCenter
        text: rootModel.name+":"
    }

    readonly property var daysName: ["pn","wt","sr","cz","pt","so","nd"]

    Row{
        anchors.verticalCenter: parent.verticalCenter
        spacing: 1
        Repeater{
            model:7
            Rectangle{
                anchors.verticalCenter: parent.verticalCenter
                width:40
                height:30
                border.width: 1
                color: isCheck? "green" : "transparent"

                property bool isCheck: rootModel.getDay(index)
                property int number: index

                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: daysName[index];
                    font.bold: true
                    font.pixelSize: 15
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        if(isCheck){
                            isCheck = false
                            rootModel.resetDay(index)
                        }
                        else{
                            isCheck = true
                            rootModel.setDay(index)
                        }
                    }
                }
            }
        }
    }
}

