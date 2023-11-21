#include "notestorage/notestorage.h"

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
  return {getObject(emt::emotAngry, note->angryLevel),
          getObject(emt::emotSad, note->sadLevel),
          getObject(emt::emotFear, note->fearLevel),
          getObject(emt::emotHappy, note->happyLevel),
          getObject(emt::emotLove, note->loveLevel)};
}

QVector<QVariant>
NoteStorage::prepareTextObject(const std::unique_ptr<NoteText> &text) const {
  return {
      getObject("body", QString::fromStdString(text->bodyTxt), quest::body),
      getObject("behavior", QString::fromStdString(text->behaviorTxt),
                quest::behavior),
      getObject("situation", QString::fromStdString(text->situationTxt),
                quest::situation),
      getObject("thoughts", QString::fromStdString(text->thoughtsTxt),
                quest::thoughts),
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
          {"emotCatg", prepareEmotObject(note)}};
}

std::unique_ptr<Note> NoteStorage::getEmptyNote() const {
  return std::make_unique<Note>(
      Note{.id = constants::database::defaultNoteID,
           .noteTextId = constants::database::defaultNoteID});
}

std::unique_ptr<NoteText> NoteStorage::getEmptyNoteDetails() const {
  return std::make_unique<NoteText>(
      NoteText{.id = constants::database::defaultNoteID});
}

void NoteStorage::parseEmotCatg(const QVariantList &data, Note &note)
{

}

QVariantMap NoteStorage::getDefaultNote() const {
  return getNoteDetails(constants::database::defaultNoteID);
}

short NoteStorage::getDefaultNoteId() {
  return constants::database::defaultNoteID;
}

void NoteStorage::addNewNote(const int &id, const QVariant &note) {
  const auto varMap = note.value<QVariantMap>();

  bool isCorrectKeys = varMap.contains("emotState");
  isCorrectKeys &= varMap.contains("emotTexts");
  isCorrectKeys &= varMap.contains("emotCatg");

  if (!isCorrectKeys) {
    qWarning() << "NoteStorage::addNewNote. "
                  "Attempts to save an object that is not a `Note`.";
    return;
  }

  const auto emotState = varMap["emotState"].value<int8_t>();
  const auto emotTexts = varMap["emotTexts"];
  const auto emotCatg = varMap["emotCatg"];
}
