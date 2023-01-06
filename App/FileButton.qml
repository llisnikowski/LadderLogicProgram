import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs

ToolButton {
    id: toolButton
    text: "  Plik  "

    onClicked: {
        if(!fileMenu.visible)
            fileMenu.open();
        else
            fileMenu.close();
    }

    Menu {
        id: fileMenu
        y: toolButton.height
        MenuItem {
            text: "Nowy projekt"
            onClicked: {
                interfaceButtons.newProject();
            }
        }
        MenuItem {
            text: "Otwórz Projekt"
            onClicked: {
                openFileDialog.open();
            }
        }
        MenuItem {
            text: "Zapisz Projekt"
            onClicked: {
                saveFileDialog.open();
            }
        }
        MenuItem {
            text: "Zamknij"
            onClicked: {
                Qt.quit();
            }
        }
    }
    FileDialog {
        id: openFileDialog
        title: "Otwórz"
        nameFilters: ["plc file (*.plc)", "text file (*.plc)", "All files (*)"]
        defaultSuffix: "plc"
        fileMode: FileDialog.OpenFile
        onAccepted: {
            var path = selectedFile.toString();
            path = path.replace(/^(file:\/{3})/,"");
            interfaceButtons.open(path);
        }
    }
    FileDialog {
        id: saveFileDialog
        title: "Zapisz"
        defaultSuffix: "plc"
        nameFilters: ["plc file (*.plc)", "text file (*.plc)", "All files (*)"]
        fileMode: FileDialog.SaveFile
        onAccepted: {
            var path = selectedFile.toString();
            path = path.replace(/^(file:\/{3})/,"");
            interfaceButtons.save(path);
        }
    }
}
