import QtQuick 2.0
import Sailfish.Silica 1.0
import com.github.biblebybyte.backend 1.0

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

    Backend {
        id: appBackend

        onSavedVersesChanged: {
            var prevVerseNo = verseNoTextField.text
            verseNoTextField.text = Number(prevVerseNo) + 1
            verseText.text = ""
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: verseDataColumn.height + Theme.paddingLarge

    Column {
        id: verseDataColumn
        width: parent.width

        PageHeader {
            id: verseEntryHeader

            title: qsTr("Verse Entry")
        }

        ComboBox {
            id: bookNameComboBox

            menu: ContextMenu {
                MenuItem { text: qsTr("Genesis") }
                MenuItem { text: qsTr("Exodus") }
                MenuItem { text: qsTr("Leviticus") }
                MenuItem { text: qsTr("Numbers") }
                MenuItem { text: qsTr("Deuteronomy") }
                MenuItem { text: qsTr("Joshua") }
                MenuItem { text: qsTr("Judges") }
                MenuItem { text: qsTr("Ruth") }
                MenuItem { text: qsTr("1 Samuel") }
                MenuItem { text: qsTr("2 Samuel") }
                MenuItem { text: qsTr("1 Kings") }
                MenuItem { text: qsTr("2 Kings") }
                MenuItem { text: qsTr("1 Chronicles") }
                MenuItem { text: qsTr("2 Chronicles") }
                MenuItem { text: qsTr("Ezra") }
                MenuItem { text: qsTr("Nehemiah") }
                MenuItem { text: qsTr("Esther") }
                MenuItem { text: qsTr("Job") }
                MenuItem { text: qsTr("Psalms") }
                MenuItem { text: qsTr("Proverbs") }
                MenuItem { text: qsTr("Ecclesiastes") }
                MenuItem { text: qsTr("Song of Solomon") }
                MenuItem { text: qsTr("Isaiah") }
                MenuItem { text: qsTr("Jeremiah") }
                MenuItem { text: qsTr("Lamentations") }
                MenuItem { text: qsTr("Ezekiel") }
                MenuItem { text: qsTr("Daniel") }
                MenuItem { text: qsTr("Hosea") }
                MenuItem { text: qsTr("Joel") }
                MenuItem { text: qsTr("Amos") }
                MenuItem { text: qsTr("Obadiah") }
                MenuItem { text: qsTr("Jonah") }
                MenuItem { text: qsTr("Micah") }
                MenuItem { text: qsTr("Nahum") }
                MenuItem { text: qsTr("Habbakuk") }
                MenuItem { text: qsTr("Zephaniah") }
                MenuItem { text: qsTr("Haggai") }
                MenuItem { text: qsTr("Zechariah") }
                MenuItem { text: qsTr("Malachi") }
                MenuItem { text: qsTr("Matthew") }
                MenuItem { text: qsTr("Mark") }
                MenuItem { text: qsTr("Luke") }
                MenuItem { text: qsTr("John") }
                MenuItem { text: qsTr("Acts") }
                MenuItem { text: qsTr("Romans") }
                MenuItem { text: qsTr("1 Corinthians") }
                MenuItem { text: qsTr("2 Corinthians") }
                MenuItem { text: qsTr("Galatians") }
                MenuItem { text: qsTr("Ephesians") }
                MenuItem { text: qsTr("Philippians") }
                MenuItem { text: qsTr("Colossians") }
                MenuItem { text: qsTr("1 Thessalonians") }
                MenuItem { text: qsTr("2 Thessalonians") }
                MenuItem { text: qsTr("1 Timothy") }
                MenuItem { text: qsTr("2 Timothy") }
                MenuItem { text: qsTr("Titus") }
                MenuItem { text: qsTr("Philemon") }
                MenuItem { text: qsTr("Hebrews") }
                MenuItem { text: qsTr("James") }
                MenuItem { text: qsTr("1 Peter") }
                MenuItem { text: qsTr("2 Peter") }
                MenuItem { text: qsTr("1 John") }
                MenuItem { text: qsTr("2 John") }
                MenuItem { text: qsTr("3 John") }
                MenuItem { text: qsTr("Jude") }
                MenuItem { text: qsTr("Revelation") }
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

            onClicked: appBackend.saveVerse(bookNameComboBox.currentIndex,
                                            chapterNoTextField.text,
                                            verseNoTextField.text,
                                            verseText.text)
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
