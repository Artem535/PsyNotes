import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

FlickablePage {
  id: root
  title: "Note"

  property int noteId: 0
  property var noteDetails: ({})

  onNoteIdChanged: {
    logic.getNoteDetails(noteId)
    noteDetails = dataModel.noteDetails
    console.log("Additional data getted!")
  }

  flickable.contentHeight: layout.height

  ColumnLayout {
    id: layout
    spacing: 40
    width: parent.width

    EmotionState {
      Layout.fillWidth: true
      Layout.preferredHeight: 70
      value: noteDetails["emotLevel"]
    }

    EmotionSelectorDynamic {
      Layout.fillWidth: true
      Layout.preferredHeight: 500
      emotCategories: noteDetails["emotLevels"]
    }

    AppTextArea {
      title: qsTr("Situation?")
      Layout.fillWidth: true
      text: noteDetails["situation"]
    }

    AppTextArea {
      title: qsTr("What are you think?")
      Layout.fillWidth: true
      text: noteDetails["thoughts"]
    }

    AppTextArea {
      title: qsTr("Your behaviour?")
      Layout.fillWidth: true
      text: noteDetails["behavior"]
    }

    AppTextArea {
      title: qsTr("What are you feel in body?")
      Layout.fillWidth: true
      text: noteDetails["body"]
    }
  }
}
