import QtQuick
import Felgo
import QtQml
import "../../logic"
import "../../model"

AppPage {
  title: "Diary"

  property alias notes: model.noteData

  AppListView {
    model: notes
    section.property: "day"
    section.delegate: SimpleSection {}
    delegate: AppListItem {
      rightText: modelData.time
      text: modelData.title
      onSelected: {
        navigationStack.push(notePage)
      }
    }
  }

  FloatingActionButton {
    iconType: IconType.plus
    visible: true
  }

  onPushed: {
    logic.fetchNoteData()
  }

  NoteModel {
    id: model
    dispatcher: logic
  }

  Logic {
    id: logic
  }

  Component {
    id: notePage
    NotePage {}
  }
}
