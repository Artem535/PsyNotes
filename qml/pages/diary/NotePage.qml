import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

FlickablePage {
    id: root
    title: "Note"

    flickable.contentHeight: layout.height

    ColumnLayout {
        id: layout
        spacing: 10
        width: parent.width

        EmotionState {
            Layout.fillWidth: true
            Layout.preferredHeight: 70
        }

        EmotionSelectorDynamic {
            Layout.fillWidth: true
            Layout.preferredHeight: 300
        }

        AppTextArea {
            title: qsTr("What are you think?")
            Layout.fillWidth: true
        }

        AppTextArea {
            title: qsTr("Your behaviour?")
            Layout.fillWidth: true
        }

        AppTextArea {
            title: qsTr("What are you feel in body?")
            Layout.fillWidth: true
        }
    }
}
