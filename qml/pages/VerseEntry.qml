import QtQuick 2.0
import Sailfish.Silica 1.0

import "verseentry.js" as VerseEntry

Page {
    id: verseEntryPage

    Component.onCompleted: addButtonUpdateTimer.start()

    function updateAddButton() {
        if ((chapterNoTextField.acceptableInput === true)
            && (verseNoTextField.acceptableInput === true)
            && (verseText.text.length > 0)) {
            addButton.enabled = true;
        } else {
            addButton.enabled = false
        }
    }


    signal itemEntered(string argBook, int argChapterNo, int argVerseNo, string argText)

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: verseDataColumn.height + Theme.paddingLarge

    Column {
        id: verseDataColumn
        width: parent.width

        PageHeader { title: qsTr("Enter a Verse") }

        ComboBox {
            id: bookNameComboBox

            menu: ContextMenu {
                MenuItem { text: qsTr("Genesis") }
                MenuItem { text: qsTr("Exodus") }
                MenuItem { text: qsTr("Leviticus") }
                MenuItem { text: qsTr("Numbers") }
                MenuItem { text: qsTr("Deuteronomy") }
            }
        }

        TextField {
            id: chapterNoTextField

            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: {
                verseNoTextField.focus = true
            }
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            labelVisible: false
            placeholderText: qsTr("Chapter No.")
            validator: IntValidator { bottom: 1; top: 150 }
            width: parent.width
        }

        TextField {
            id: verseNoTextField

            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: {
                verseText.focus = true
            }
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            labelVisible: false
            placeholderText: qsTr("Verse No.")
            validator: IntValidator { bottom: 1; top: 176 }
            width: parent.width
        }


        TextArea {
            id: verseText

            placeholderText: qsTr("Verse Text")
            width: parent.width
        }

        Button {
            id: addButton

            anchors.horizontalCenter: parent.horizontalCenter
            enabled: false
            text: qsTr("Add")
        }
    }

    Timer {
        id: addButtonUpdateTimer

        interval: 100 // ms
        repeat: true

        onTriggered: updateAddButton()
    }
    }
}
