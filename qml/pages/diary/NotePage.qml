import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

AppPage {
    id: root
    title: "Note"

    ColumnLayout {
        id: layout
        spacing: 10
        width: parent.width

        EmotionState {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
        }
    }
}
