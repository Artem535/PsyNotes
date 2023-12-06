#include "notestorage/notestorage.h"
#include "notestorage.h"

NoteStorage::NoteStorage(QObject *parent) : QObject{parent} {
  mSqlNoteBase = QSqlDatabase::addDatabase("QSQLITE");
  mSqlNoteBase.setDatabaseName(constants::database::databaseName);

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
  return {getObject(emt::emotAngry, query.value("angryLevel")),
          getObject(emt::emotSad, query.value("sadLevel")),
          getObject(emt::emotFear, query.value("fearLevel")),
          getObject(emt::emotHappy, query.value("happyLevel")),
          getObject(emt::emotLove, query.value("loveLevel"))};
}

QVector<QVariant> NoteStorage::prepareTextObject(const QSqlQuery &query) const {
  return {
      getObject(noteDetails::body, query.value("bodyTxt"), quest::body),
      getObject(noteDetails::behavior, query.value("behaviorTxt"),
                quest::behavior),
      getObject(noteDetails::situation, query.value("situationTxt"),
                quest::situation),
      getObject(noteDetails::thoughts, query.value("thoughtsTxt"),
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
      qDebug() << "Exception during processing query result:" << e.what();
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

QVariantMap NoteStorage::getNoteDetails(const int &noteId) {
  QVariantMap res;
  QVariantMap bindings{{":id", QVariant::fromValue(noteId)}};
  execSelectQueryTempl(
      constants::sql::getFullNoteOnId,
      [&res, this](const QSqlQuery &query) {
        res.insert({{"emotState", query.value("emotState")},
                    {"emotTexts", prepareTextObject(query)},
                    {"emotCtg", prepareEmotObject(query)}});
      },
      bindings);
  return res;
}

QVariantMap NoteStorage::getDefaultNote() {
  return getNoteDetails(constants::database::defaultNoteID);
}

short NoteStorage::getDefaultNoteId() const {
  return constants::database::defaultNoteID;
}

int NoteStorage::addNewNote(const int &id, const QVariant &note) {
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
  {
    QVariantMap emotBind;
    emotBind = parseObjects<int>(varMap["emotCtg"], getEmotCtgParameters());
    emotBind.insert({{":emotState", varMap["emotState"]}});
    insertQueryTempl(constants::sql::insertNewEmotTemplate, emotBind,
                     mLastEmotId);
  }

  {
    QVariantMap textBind;
    textBind =
        parseObjects<QString>(varMap["emotTexts"], getNoteDetailsParameters());
    insertQueryTempl(constants::sql::insertNewTextTemplate, textBind,
                     mLastTextId);
  }

  QVariantMap noteBind{{":emotId", QVariant::fromValue(mLastEmotId)},
                       {":noteTextId", QVariant::fromValue(mLastTextId)}};
  if (mLastNoteId == id) {
    noteBind.insert({{":id", mLastNoteId}});
    insertQueryTempl(constants::sql::replaceNote, noteBind, mLastNoteId);
  } else {
    insertQueryTempl(constants::sql::insertNewNoteTemplate, noteBind,
                     mLastNoteId);
  }
  return mLastNoteId;
}

QMap<QString, QString> NoteStorage::getEmotCtgParameters() const {
  return {
      {emt::emotAngry, ":angryLevel"}, {emt::emotSad, ":sadLevel"},
      {emt::emotFear, ":fearLevel"},   {emt::emotHappy, ":happyLevel"},
      {emt::emotLove, ":loveLevel"},
  };
}

QMap<QString, QString> NoteStorage::getNoteDetailsParameters() const {
  return {
      {noteDetails::body, ":body"},
      {noteDetails::behavior, ":behavior"},
      {noteDetails::thoughts, ":thoughts"},
      {noteDetails::situation, ":situation"},
  };
}
