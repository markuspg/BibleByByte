import QtQuick 2.0
import Sailfish.Silica 1.0
import com.github.biblebybyte.backend 1.0

Page {
    id: verseCheckPage

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Component.onCompleted: appBackend.requestNextVerse()

    Backend {
        id: appBackend
    }

    SilicaFlickable {
        anchors.fill: parent

    PageHeader {
        id: verseCheckHeader

        title: qsTr("Verse Check")
    }

    Label {
        id: bookLabel

        anchors.top: verseCheckHeader.bottom
        text: appBackend.checkedBook
        width: parent.width
    }

    Label {
        id: chapterNoLabel

        anchors.top: bookLabel.bottom
        text: appBackend.checkedChapterNo
        width: parent.width
    }

    Label {
        id: verseNoLabel

        anchors.top: chapterNoLabel.bottom
        text: appBackend.checkedVerseNo
        width: parent.width
    }

    TextArea {
        id: verseTextArea

        anchors.top: verseNoLabel.bottom
        readOnly: true
        width: parent.width
    }

    Button {
        id: showButton

        anchors.top: verseTextArea.bottom
        text: qsTr("Show")
        width: parent.width

        onClicked: {
            verseTextArea.text = appBackend.checkedVerseText
        }
    }

    Row {
        anchors.top: showButton.bottom
        width: parent.width

        Button {
            id: correctButton

            text: qsTr("Correct")
            width: parent.width / 2

            onClicked: {
                verseTextArea.text = ""
                appBackend.verseAnsweredRightly()
            }
        }

        Button {
            id: wrongButton

            text: qsTr("Wrong")
            width: parent.width / 2

            onClicked: {
                verseTextArea.text = ""
                appBackend.verseAnsweredWrongly()
            }
        }
    }

    }
}
