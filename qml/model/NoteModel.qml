import QtQuick
import Felgo
import PsyNotes

Item {
  id: root

  property alias dispatcher: logicConnection.target
  readonly property alias noteData: _.noteData
  readonly property alias noteDetails: _.noteDetails

  Connections {
    id: logicConnection

    onFetchNoteData: {
      _.noteData = storage.getNoteList()
    }

    onGetNoteDetails: id => {
                        _.noteDetails = storage.getNoteDetails(id)
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
  }
}
