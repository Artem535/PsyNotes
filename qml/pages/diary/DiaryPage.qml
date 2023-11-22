import QtQuick
import Felgo
import QtQml
import "../../logic"
import "../../model"

AppPage {
  title: "Diary"

  AppListView {
    model: dataModel.noteData
    section.property: "day"
    section.delegate: SimpleSection {}
    delegate: AppListItem {
      rightText: modelData.time
      text: modelData.title
      onSelected: {
        navigationStack.push(notePage, {
                               "noteId": modelData.id
                             })
      }
    }
  }

  FloatingActionButton {
    iconType: IconType.plus
    visible: true
    onClicked: {
      logic.getDefaultNoteId()
      navigationStack.push(notePage, {
                             "noteId": dataModel.defaultNoteId
                           })
    }
  }

  onPushed: {
    logic.fetchNoteData()
  }

  NoteModel {
    id: dataModel
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
