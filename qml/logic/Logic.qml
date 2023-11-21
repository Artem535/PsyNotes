import QtQuick

Item {
  signal fetchNoteData

  signal getNoteDetails(int id)

  signal getDefaultNote

  signal getDefaultNoteId

  signal saveNote(int id, var note)
}
