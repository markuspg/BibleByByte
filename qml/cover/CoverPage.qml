import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    Label {
        id: coverLabel

        anchors.centerIn: parent
        font.pixelSize: Theme.fontSizeLarge
        horizontalAlignment: Text.AlignHCenter
        text: qsTr("Shew me thy ways, O Lord; teach me thy paths. (Ps 25:4)")
        width: parent.width
        wrapMode: Text.WordWrap
    }
}
