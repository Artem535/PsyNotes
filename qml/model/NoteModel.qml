import QtQuick
import Felgo
import PsyNotes

Item {
  id: root

  property alias dispatcher: logicConnection.target
  readonly property alias noteData: _.noteData
  readonly property alias noteDetails: _.noteDetails
  readonly property alias defaultNoteId: _.defaultNoteId

  Connections {
    id: logicConnection

    onFetchNoteData: {
      _.noteData.length = 0
      _.noteData = storage.getNoteList()
    }

    onGetNoteDetails: id => {
                        _.noteDetails = storage.getNoteDetails(id)
                      }

    onGetDefaultNote: {
      _.noteDatails = storage.getDefaultNote()
    }

    onGetDefaultNoteId: {
      _.defaultNoteId = storage.getDefaultNoteId()
    }

    onSaveNote: (id, note) => {
                  var noteId = storage.addNewNote(id, note)
                }
  }

  NoteStorage {
    id: storage
  }

  // Private part
  Item {
    id: _
    property var noteData: []
    property var noteDetails: ({})
    property int defaultNoteId: 0
  }
}
