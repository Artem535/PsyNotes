#include "notestorage/notestorage.h"
#include "notestorage.h"

NoteStorage::NoteStorage(QObject *parent) : QObject{parent} {
  mSqlNoteBase = QSqlDatabase::addDatabase("QSQLITE");
  mSqlNoteBase.setDatabaseName(constants::database::kDatabaseName);

  const QStringList scripts{
      sql::createNoteTable,        sql::createEmotTable,
      sql::createNoteTextTable,    sql::insertDefaultValueEmot,
      sql::insertDefaultValueNote, sql::insertDefaultValueNoteText};

  mSqlNoteBase.open();
  execQuery(scripts);
}

NoteStorage::~NoteStorage() { mSqlNoteBase.close(); }

QVector<QVariant> NoteStorage::getNoteList() {
  QVariantList notes;
  // NOTE: If in database will be a lot data, then it will be slow.
  // Maybe the correct will use omp.
  execSelectQuery(
      constants::sql::getShortNotes, [&notes](const QSqlQuery &query) {
        notes.push_back(QVariantMap{{"id", query.value("id")},
                                    {"title", query.value("title")},
                                    {"day", query.value("dateValue")},
                                    {"time", query.value("timeValue")}});
      });

  return QVector<QVariant>::fromList(notes);
}

QVector<QVariant> NoteStorage::prepareEmotObject(const QSqlQuery &query) const {
  return {getObject(emotions::kEmotAngry, query.value("angryLevel")),
          getObject(emotions::kEmotSad, query.value("sadLevel")),
          getObject(emotions::kEmotFear, query.value("fearLevel")),
          getObject(emotions::kEmotHappy, query.value("happyLevel")),
          getObject(emotions::kEmotLove, query.value("loveLevel"))};
}

QVector<QVariant>
NoteStorage::prepareNoteDetailsObject(const QSqlQuery &query) const {
  return {
      getObject(noteDetails::kBody, query.value("bodyTxt"), questions::kBody),
      getObject(noteDetails::kBehavior, query.value("behaviorTxt"),
                questions::kBehavior),
      getObject(noteDetails::kSituation, query.value("situationTxt"),
                questions::kSituation),
      getObject(noteDetails::kThoughts, query.value("thoughtsTxt"),
                questions::kThoughts),
  };
}

QVariantMap NoteStorage::getObject(const QString &key,
                                   const QVariant &value) const {
  return {{"name", key}, {"value", value}};
}

QVariantMap NoteStorage::getObject(const QString &key, const QVariant &value,
                                   const QVariant &addtValue) const noexcept {
  return {{"name", key}, {"value", value}, {"secondValue", addtValue}};
}

bool NoteStorage::execQuery(const QString &script) {
  QSqlQuery query(script);
  return query.exec();
}


bool NoteStorage::execQuery(const QStringList &scripts) {
  QSqlQuery query;
  bool allFine{true};

  for (const auto &script : scripts)
    allFine &= query.exec(script);

  return allFine;
}


void NoteStorage::insertQueryTempl(const QString &script,
                                   const QVariantMap &bindings, int &lastId) {
  QSqlQuery query;
  query.prepare(script);
  std::for_each(bindings.constKeyValueBegin(), bindings.constKeyValueEnd(),
                [&](const auto &it) {
                  qDebug() << "WHAT?" << it.first << it.second;
                  query.bindValue(it.first, it.second);
                });
  if (query.exec())
    lastId = query.lastInsertId().toInt();
}

bool NoteStorage::execSelectQuery(QSqlQuery &query, const auto &process) {
  if (!query.exec()) {
    logMessage("Error executing query:" + query.lastError().text());
    return false;
  }

  while (query.next()) {
    try {
      process(query);
    } catch (const std::exception &e) {
      logMessage("Exception during processing query result: " +
                     QString(e.what()),
                 QtWarningMsg);
      return false;
    }
  }

  return true;
}

bool NoteStorage::execSelectQuery(const QString &script, const auto &process) {
  QSqlQuery query(script);
  return execSelectQuery(query, process);
}

bool NoteStorage::execSelectQueryTempl(const QString &script,
                                       const auto &process,
                                       const QVariantMap &bindings) {
  QSqlQuery query;
  query.prepare(script);
  std::for_each(bindings.constKeyValueBegin(), bindings.constKeyValueEnd(),
                [&](const auto &it) { query.bindValue(it.first, it.second); });
  return execSelectQuery(query, process);
}


void NoteStorage::parseAndInsertObject(NoteStorage::ObjectCtgTypes type,
                                     const QVariant &object,
                                     const QMap<QString, QString> &params,
                                     const QVariant &additionalObject) {
  switch (type) {
  case ObjectCtgTypes::emot: {
    QVariantMap emotBind;
    emotBind = parseObjects<int>(object, params);
    emotBind.insert({{":emotState", additionalObject.toDouble()}});
    insertQueryTempl(constants::sql::insertNewEmotTemplate, emotBind,
                     mLastEmotId);
    break;
  }
  case ObjectCtgTypes::text: {
    QVariantMap textBind;
    textBind = parseObjects<QString>(object, params);
    insertQueryTempl(constants::sql::insertNewTextTemplate, textBind,
                     mLastTextId);
    break;
  }
  case ObjectCtgTypes::note: {
    QVariantMap noteBind{{":emotId", QVariant::fromValue(mLastEmotId)},
                         {":noteTextId", QVariant::fromValue(mLastTextId)}};
    if (const int noteId{object.toInt()};
        noteId != constants::database::kDefaultNoteID) {
      noteBind.insert({{":id", noteId}});
      insertQueryTempl(constants::sql::replaceNote, noteBind, mLastNoteId);
    } else {
      insertQueryTempl(constants::sql::insertNewNoteTemplate, noteBind,
                       mLastNoteId);
    }
    break;
  }
  default:
    break;
  }
}

QVariantMap NoteStorage::getNoteDetails(const int &noteId) {
  QVariantMap res;
  QVariantMap bindings{{":id", QVariant::fromValue(noteId)}};
  execSelectQueryTempl(
      constants::sql::getFullNoteOnId,
      [&res, this](const QSqlQuery &query) {
        res.insert({{"emotState", query.value("emotState")},
                    {"emotTexts", prepareNoteDetailsObject(query)},
                    {"emotCtg", prepareEmotObject(query)}});
      },
      bindings);
  return res;
}

QVariantMap NoteStorage::getDefaultNote() {
  return getNoteDetails(constants::database::kDefaultNoteID);
}

short NoteStorage::getDefaultNoteId() const {
  return constants::database::kDefaultNoteID;
}

int NoteStorage::addNewNote(const int &id, const QVariant &note) {
  const QVariantMap varMap = note.toMap();

  bool isCorrectKeys = varMap.contains("emotState");
  isCorrectKeys &= varMap.contains("emotTexts");
  isCorrectKeys &= varMap.contains("emotCtg");

  if (!isCorrectKeys) {
    qWarning() << "NoteStorage::addNewNote. "
                  "Attempts to save an object that is not a `Note`.";
    return constants::database::kDefaultNoteID;
  }

  // Parse and add to the mNoteDetailsBase emotTexts.
  parseAndInsertObject(NoteStorage::ObjectCtgTypes::emot, varMap["emotCtg"],
                     getEmotCtgParameters(), varMap["emotState"]);
  parseAndInsertObject(NoteStorage::ObjectCtgTypes::text, varMap["emotTexts"],
                     getNoteDetailsParameters());
  parseAndInsertObject(NoteStorage::ObjectCtgTypes::note, QVariant(id));

  return mLastNoteId;
}

QMap<QString, QString> NoteStorage::getEmotCtgParameters() const {
  return {
      {emotions::kEmotAngry, ":angryLevel"},
      {emotions::kEmotSad, ":sadLevel"},
      {emotions::kEmotFear, ":fearLevel"},
      {emotions::kEmotHappy, ":happyLevel"},
      {emotions::kEmotLove, ":loveLevel"},
  };
}

QMap<QString, QString> NoteStorage::getNoteDetailsParameters() const {
  return {
      {noteDetails::kBody, ":body"},
      {noteDetails::kBehavior, ":behavior"},
      {noteDetails::kThoughts, ":thoughts"},
      {noteDetails::kSituation, ":situation"},
  };
}
