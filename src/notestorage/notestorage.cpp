#include "notestorage/notestorage.h"
#include "notestorage.h"

NoteStorage::NoteStorage(QObject *parent) : QObject{parent} {
  obx::Options options{create_obx_model()};
  mStore = std::make_unique<obx::Store>(options);
  mNoteBase = std::make_unique<obx::Box<Note>>(*(mStore.get()));
  Note test_note = {
      .time = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch()),
      .title = "test"};
  mNoteBase->put(test_note);
}

QVariantList NoteStorage::getNoteList() {
  QVariantList notes;
  for (const auto &note : mNoteBase->getAll()) {
    const auto unixTime = QDateTime::fromMSecsSinceEpoch(note->time);
    QVariantMap shortNote{
        {"id", QVariant::fromValue(note->id)},
        {"title", QVariant::fromValue(QString::fromStdString(note->title))},
        {"day", QVariant::fromValue(unixTime.date().toString("dd.MM.yy"))},
        {"time", QVariant::fromValue(unixTime.time().toString("HH:mm"))}};
    notes.append(shortNote);
  }
  return notes;
}
