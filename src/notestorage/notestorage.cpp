#include "notestorage/notestorage.h"
#include "notestorage.h"

NoteStorage::NoteStorage(QObject *parent) : QObject{parent} {
  obx::Options options{create_obx_model()};
  mStore = std::make_unique<obx::Store>(options);
  mNoteBase = std::make_unique<obx::Box<Note>>(*(mStore.get()));
  mNoteDetailsBase = std::make_unique<obx::Box<NoteText>>(*(mStore.get()));
  Note test_note = {
      .time = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch()),
      .title = "test",
      .visible = true};
  mNoteBase->put(test_note);
}

QVector<QVariant> NoteStorage::getNoteList() {
  QVariantList notes;
  // NOTE: If in database will be a lot data, then it will be slow.
  // Maybe the correct will use omp.
  for (const auto &note : mNoteBase->getAll()) {
    if (note->visible) {
      const auto unixTime = QDateTime::fromMSecsSinceEpoch(note->time);
      QVariantMap shortNote{{"id", QVariant::fromValue(note->id)},
                            {"title", QString::fromStdString(note->title)},
                            {"day", unixTime.date().toString("dd.MM.yy")},
                            {"time", unixTime.time().toString("HH:mm")}};
      notes.append(shortNote);
    }
  }
  return QVector<QVariant>::fromList(notes);
}

QVector<QVariant>
NoteStorage::prepareEmotObject(const std::unique_ptr<Note> &note) const {
  const auto getObject = [](const QString &emotName,
                            const uint8_t &level) -> QVariantMap {
    return {{"name", emotName}, {"level", level}};
  };

  return {getObject(emt::emotAngry, note->angryLevel),
          getObject(emt::emotSad, note->sadLevel),
          getObject(emt::emotFear, note->fearLevel),
          getObject(emt::emotHappy, note->happyLevel),
          getObject(emt::emotLove, note->loveLevel)};
}

QVariantMap NoteStorage::getNoteDetails(const obx_id &noteId) const {
  const auto note = noteId == constants::database::emptyNoteID
                        ? getEmptyNote()
                        : mNoteBase->get(noteId);

  return {{"behavior", ""},
          {"emotLevel", -1},
          {"situation", "TEST_STRING"},
          {"body", "TEST_STRING"},
          {"thoughts", "TEST_STRING"},
          {"body", "TEST_STRING"},
          {"emotLevels", prepareEmotObject(note)}};
}

std::unique_ptr<Note> NoteStorage::getEmptyNote() const {
  auto note = std::make_unique<Note>();
  note->id = constants::database::emptyNoteID;
  return note;
}

QVariantMap NoteStorage::getDefaultNote() const {
  return getNoteDetails(constants::database::emptyNoteID);
}
