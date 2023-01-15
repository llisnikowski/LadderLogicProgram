import QtQuick 2.12
import QtQuick.Controls 2.15

SplitView{
    id: mainSplitView
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
    ProgramView {
        id: programView
        clip: true
        SplitView.minimumWidth: 200
        implicitWidth: 500
        SplitView.preferredWidth: 1000
        SplitView.fillWidth: true
    }
    SplitView{
        id: rightView
        clip: true
        implicitWidth: 600
        SplitView.minimumWidth: 150
        SplitView.maximumWidth: 1200
        orientation: Qt.Vertical

        Item{
            clip: true
            implicitHeight: 400
            SplitView.minimumHeight: 100
            SplitView.fillHeight: true
            Component.onCompleted: {
                propertiesList.setContainerParent(this)
            }
        }
        Item{
            clip: true
            SplitView.minimumHeight: 100
            implicitHeight: rightView.height / 3
            SplitView.maximumHeight: 700
            Component.onCompleted: {
                consoleLog.parent = this
            }
        }
    }
}

