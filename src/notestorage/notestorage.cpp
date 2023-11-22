#include "notestorage/notestorage.h"
#include "notestorage.h"

NoteStorage::NoteStorage(QObject *parent) : QObject{parent} {
  obx::Options options{create_obx_model()};
  mStore = std::make_unique<obx::Store>(options);
  mNoteBase = std::make_unique<obx::Box<Note>>(*(mStore.get()));
  mNoteDetailsBase = std::make_unique<obx::Box<NoteText>>(*(mStore.get()));
}

QVector<QVariant> NoteStorage::getNoteList() {
  QVariantList notes;
  // NOTE: If in database will be a lot data, then it will be slow.
  // Maybe the correct will use omp.
  for (const auto &note : mNoteBase->getAll()) {
    if (note->visible) {
      notes.append(createShortNote(*note));
    }
  }
  return QVector<QVariant>::fromList(notes);
}

QVariant NoteStorage::getNote(const obx_id &id) {
  const auto note = mNoteBase->get(id);
  return note->visible ? createShortNote(*note) : QVariant();
}

QVector<QVariant>
NoteStorage::prepareEmotObject(const std::unique_ptr<Note> &note) const {
  return {getObject(emt::emotAngry, note->angryLevel),
          getObject(emt::emotSad, note->sadLevel),
          getObject(emt::emotFear, note->fearLevel),
          getObject(emt::emotHappy, note->happyLevel),
          getObject(emt::emotLove, note->loveLevel)};
}

QVector<QVariant>
NoteStorage::prepareTextObject(const std::unique_ptr<NoteText> &text) const {
  return {
      getObject(noteDetails::body, QString::fromStdString(text->bodyTxt),
                quest::body),
      getObject(noteDetails::behavior,
                QString::fromStdString(text->behaviorTxt), quest::behavior),
      getObject(noteDetails::situation,
                QString::fromStdString(text->situationTxt), quest::situation),
      getObject(noteDetails::thoughts,
                QString::fromStdString(text->thoughtsTxt), quest::thoughts),
  };
}

QVariantMap NoteStorage::getObject(const QString &key,
                                   const QVariant &value) const {
  return {{"name", key}, {"value", value}};
}
QVariantMap NoteStorage::getObject(const QString &key, const QVariant &value,
                                   const QVariant &addtValue) const {
  return {{"name", key}, {"value", value}, {"secondValue", addtValue}};
}

QVariantMap NoteStorage::getNoteDetails(const obx_id &noteId) const {

  const auto note = noteId == constants::database::defaultNoteID
                        ? getEmptyNote()
                        : mNoteBase->get(noteId);

  const auto text = note->noteTextId == constants::database::defaultNoteID
                        ? getEmptyNoteDetails()
                        : mNoteDetailsBase->get(note->noteTextId);

  return {{"emotState", note->emotState},
          {"emotTexts", prepareTextObject(text)},
          {"emotCtg", prepareEmotObject(note)}};
}

std::unique_ptr<Note> NoteStorage::getEmptyNote() const {
  return std::make_unique<Note>(
      Note{.id = constants::database::defaultNoteID,
           .noteTextId = constants::database::defaultNoteID,
           .visible = false});
}

std::unique_ptr<NoteText> NoteStorage::getEmptyNoteDetails() const {
  return std::make_unique<NoteText>(
      NoteText{.id = constants::database::defaultNoteID});
}

QVariantMap NoteStorage::getDefaultNote() const {
  return getNoteDetails(constants::database::defaultNoteID);
}

short NoteStorage::getDefaultNoteId() {
  return constants::database::defaultNoteID;
}

obx_id NoteStorage::addNewNote(const obx_id &id, const QVariant &note) {
  const QVariantMap varMap = note.toMap();

  bool isCorrectKeys = varMap.contains("emotState");
  isCorrectKeys &= varMap.contains("emotTexts");
  isCorrectKeys &= varMap.contains("emotCtg");

  if (!isCorrectKeys) {
    qWarning() << "NoteStorage::addNewNote. "
                  "Attempts to save an object that is not a `Note`.";
    return constants::database::defaultNoteID;
  }

  // Parse and add to the mNoteDetailsBase emotTexts.
  NoteText resultNoteDetails{.id = constants::database::defaultNoteID};
  parseObjects<std::string>(varMap["emotTexts"],
                            getNoteDetailsMap(resultNoteDetails));
  const obx_id noteDetailsId{mNoteDetailsBase->put(resultNoteDetails)};

  // Parse and add to mNoteBase a note.
  Note resultNote{
      .id = id,
      .time = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch()),
      .noteTextId = noteDetailsId,
      .emotState = static_cast<int8_t>(varMap["emotState"].toInt()),
      .title = "Test Tile",
      .visible = true};
  parseObjects<int8_t>(varMap["emotCtg"], getEmotCtgMap(resultNote));
  return mNoteBase->put(resultNote);
}

QMap<QString, std::reference_wrapper<int8_t>>
NoteStorage::getEmotCtgMap(Note &note) {
  return {
      {emt::emotAngry, std::ref(note.angryLevel)},
      {emt::emotSad, std::ref(note.sadLevel)},
      {emt::emotFear, std::ref(note.fearLevel)},
      {emt::emotHappy, std::ref(note.happyLevel)},
      {emt::emotLove, std::ref(note.loveLevel)},
  };
}

QMap<QString, std::reference_wrapper<std::string>>
NoteStorage::getNoteDetailsMap(NoteText &note) {
  return {
      {noteDetails::body, std::ref(note.bodyTxt)},
      {noteDetails::behavior, std::ref(note.behaviorTxt)},
      {noteDetails::thoughts, std::ref(note.thoughtsTxt)},
      {noteDetails::situation, std::ref(note.situationTxt)},
  };
}

QVariant NoteStorage::createShortNote(const Note &note) {
  const auto unixTime = QDateTime::fromMSecsSinceEpoch(note.time);
  return QVariantMap{{"id", QVariant::fromValue(note.id)},
                     {"title", QString::fromStdString(note.title)},
                     {"day", unixTime.date().toString("dd.MM.yy")},
                     {"time", unixTime.time().toString("HH:mm")}};
}
