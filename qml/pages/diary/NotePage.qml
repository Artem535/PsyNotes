import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

FlickablePage {
  id: root
  title: "Note"

  property int noteId: -1
  property var noteDetails: [{}]

  onNoteIdChanged: {
    logic.getNoteDetails(noteId)
    noteDetails = dataModel.noteDetails
    console.log("Additional data getted!")
  }

  flickable.contentHeight: layout.height

  rightBarItem: NavigationBarItem {
    IconButtonBarItem {
      id: saveButton
      anchors.centerIn: parent
      iconSize: dp(Theme.navigationBar.defaultIconSize)
      iconType: IconType.save

      onClicked: {
        logic.saveNote(noteId, {
                         "emotState": currentState.value,
                         "emotTexts": noteDetails["emotTexts"],
                         "emotCtg": emotSpectrum.emotCategories
                       })
        logic.fetchNoteData()
        navigationStack.pop()
      }
    }
  }

  JsonListModel {
    id: jsonModel
    source: noteDetails["emotTexts"]
  }

  ColumnLayout {
    id: layout
    spacing: 40
    width: parent.width

    EmotionState {
      id: currentState
      Layout.fillWidth: true
      Layout.preferredHeight: 70
      value: noteDetails["emotState"]
    }

    EmotionSpectrum {
      id: emotSpectrum
      Layout.fillWidth: true
      Layout.preferredHeight: 500
      emotCategories: noteDetails["emotCtg"]
    }

    Repeater {
      model: jsonModel
      AppTextArea {
        id: textSituation
        title: model.secondValue
        text: model.value
        Layout.fillWidth: true
        onTextChanged: noteDetails["emotTexts"][index].value = text
      }
    }
  }
}
