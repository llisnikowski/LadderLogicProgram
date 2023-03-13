import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id:infoWindow
    width: 400
    height: 300

    Item{
        anchors.fill: parent
        anchors.margins: 7

        Text {
            id: descritpion
            width: parent.width
            height: parent.height - author.height

            text: "Program zrobiony w ramach projeku inżynierskiego. Pozwala "+
                  "na zaprogramowanie sterownika PLC.\n\n" +
                  "Komunikuje się ze sterownikiem bazującym na mikrokontrolerze STM32, "+
                  "zrobionym w ramach projektu w kole naukowym.\n"+
                  "Program umożliwia:\n"+
                  "  - tworzenie programy w języku Ld za pomocą mechanizmu Drag and drop,\n" +
                  "  - komunikację ze sterownikiem,\n" +
                  "  - zapis i odczyt programu z pliku.\n"
            font.pixelSize: 13
            color: "white"
            wrapMode: Text.WordWrap
            horizontalAlignment: TextArea.AlignJustify
        }
        TextEdit {
            id: author

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 7
            width: parent.width
            height: 50

            text: "Autor:\n" + "Łukasz Liśnikowski, l.lisnikowski@gmail.com \n"+
                  "Project Link: https://github.com/llisnikowski/LadderLogicProgram"
            font.pixelSize: 13
            color: "white"
            readOnly: true
            wrapMode: Text.WordWrap
        }

    }

}
