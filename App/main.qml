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
        ToolMenu {
            anchors.fill: parent
        }
    }

    SplitView{
        anchors.fill: parent
        orientation: Qt.Horizontal
        clip: true
        LdSymbolsBar {
            id: symbolsView
            clip: true
            implicitWidth: 80
            SplitView.minimumWidth: 70
            SplitView.maximumWidth: 100
        }
        Item {
            id: programView
            clip: true
            SplitView.minimumWidth: 50
            SplitView.fillWidth: true

        }
        Item{
            id: rightView
            clip: true
            implicitWidth: 600
            SplitView.minimumWidth: 150
            SplitView.maximumWidth: 1000
        }
    }

}
