import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("PLC")

    header: ToolBar {
        id: toolBar
        ToolMenu {
            anchors.fill: parent
        }
    }

    SplitView{
        id: mainSplitView
        anchors.fill: parent
        orientation: Qt.Horizontal
        clip: true
        SplitView.fillHeight: true

        LdSymbolsBar {

            id: symbolsView
            clip: true
            implicitWidth: 80
//            height: parent.height
            SplitView.minimumWidth: 70
            SplitView.maximumWidth: 100
//            SplitView.minimumHeight: mainSplitView.height
//            SplitView.fillHeight : true
//            SplitView.fillHeight: true
//            Component.onCompleted: {
//                console.log(width)
//                console.log(symbolsView.height)
//            }
        }
        ProgramView {
            id: programView
            clip: true
            SplitView.minimumWidth: 200
            SplitView.maximumWidth: 1000
            implicitWidth: 500
            SplitView.preferredWidth: 1000

            SplitView.fillWidth: true

        }
        SplitView{
            id: rightView
            clip: true
            implicitWidth: 600
            SplitView.minimumWidth: 150
            SplitView.maximumWidth: 1000

            orientation: Qt.Vertical

            Item{
                clip: true
                implicitHeight: 400
                SplitView.minimumHeight: 100
                SplitView.fillHeight: true
                Component.onCompleted: {
                    propertyList.parent = this
                }
            }
            Item{
                clip: true
                SplitView.minimumHeight: 100
                implicitHeight: rightView.height / 3
                SplitView.maximumHeight: 700
                SplitView.fillWidth: true
                Component.onCompleted: {
                    consoleLog.parent = this
                }
            }
        }
    }

}
