import QtQuick

Item {
  signal fetchNoteData

  signal getNoteDetails(int id)

  signal getDefaultNote

  signal getDefaultNoteId

  signal storageUpdated

  signal saveNote(int id, var note)
}
