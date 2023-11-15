import QtQuick
import Felgo
import PsyNotes

Item {
  id: root

  property alias dispatcher: logicConnection.target
  readonly property alias noteData: _.noteData

  Connections {
    id: logicConnection
    onFetchNoteData: {
      _.noteData = storage.getNoteList()
    }
  }

  NoteStorage {
    id: storage
  }

  // Private part
  Item {
    id: _
    property var noteData: []
  }
}
