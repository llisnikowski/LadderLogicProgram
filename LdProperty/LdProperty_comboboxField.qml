import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property var rootModel;
    id:mainItem
    width: 64
    height: 64


    ComboBox{
        id:selectTypeCombobox
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset:6;
        anchors.horizontalCenterOffset:(64-width)/2-2;
        width:15;
        height:36;
        font.pixelSize: 12
        model: rootModel.model
        currentIndex: rootModel.value;

        delegate: ItemDelegate {
            width: mainItem.width
            text: selectTypeCombobox.model[index]
            font.pixelSize: 14
        }

        background: Rectangle {
            id: comboboxBackground
            color:"grey"
            states: [
                State{
                    when: selectTypeCombobox.activeFocus
                    PropertyChanges {
                        target: comboboxBackground
                        color: "darkgrey"
                    }
                }
            ]
        }
        popup: Popup {
            x: -62+15
            y: selectTypeCombobox.height
            width: 64
            margins: 0
            padding: 0

            contentItem: ListView {
                width: 64
                implicitHeight: contentHeight
                model: selectTypeCombobox.delegateModel
                currentIndex: selectTypeCombobox.highlightedIndex
            }
        }
        indicator { //strzałka
            width: 15;
        }
        onActivated: {
            rootModel.value = currentIndex
        }
        onFocusChanged: {
            parent.onFocusChanged(selectTypeCombobox.activeFocus);
        }
    }
}
