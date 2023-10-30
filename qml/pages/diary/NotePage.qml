import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

FlickablePage {
    id: root
    title: "Note"

    flickable.contentHeight: layout

    ColumnLayout {
        id: layout
        spacing: 10
        width: parent.width

        EmotionState {
            Layout.fillWidth: true
            Layout.preferredHeight: 70
        }

        EmotionSelector {
            Layout.fillWidth: true
            Layout.preferredHeight: 300
        }

        RowLayout {
            Layout.preferredHeight: 40
            Layout.margins: 10

            AppText {
                text: "Detailed"
                Layout.fillHeight: true
            }

            AppSwitch {
                id: switchItem
            }
        }
    }
}
