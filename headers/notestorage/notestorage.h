#pragma once
#include "constants.hpp"
#include "sqlscripts.hpp"
#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>
#include <QtQuick>
#include <cstdint>
#include <functional>
#include <memory>
#include <source_location>
#include <utility>

namespace emotions = constants::emotions;
namespace questions = constants::questionsLabels;
namespace noteDetails = constants::noteDetails;
namespace sql = constants::sql;

using srcLoc = std::source_location;

class NoteStorage : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit NoteStorage(QObject *parent = nullptr);
  ~NoteStorage() override;
  Q_INVOKABLE QVector<QVariant> getNoteList();
  Q_INVOKABLE QVariantMap getNoteDetails(const int &noteId);
  Q_INVOKABLE QVariantMap getDefaultNote();
  Q_INVOKABLE short getDefaultNoteId() const;
  Q_INVOKABLE int addNewNote(const int &id, const QVariant &note);

private:
  enum class ObjectCtgTypes { emot, text, note };
  int mLastTextId = constants::database::kDefaultNoteID;
  int mLastEmotId = constants::database::kDefaultNoteID;
  int mLastNoteId = -1;
  QSqlDatabase mSqlNoteBase;

  int mIdDefaultNote;

  /**
   * @brief Prepare the emot object for the given QSqlQuery.
   * @param query The QSqlQuery object to extract values from
   * @return A QVector<QVariant> containing the prepared emot objects
   */
  QVector<QVariant> prepareEmotObject(const QSqlQuery &query) const;

  /**
   * @brief Prepare the note details object for the given QSqlQuery.
   * @param query The QSqlQuery object to extract values from
   * @return A QVector<QVariant> containing the prepared emot objects
   */
  QVector<QVariant> prepareNoteDetailsObject(const QSqlQuery &query) const;

  /**
   * @brief Returns a QVariantMap object that contains the specified key, value, and
   * additional value.
   * @param key The name of the key.
   * @param value The value associated with the key.
   * @return A QVariantMap object that contains the key, value, and additional
   * value.
   */
  QVariantMap getObject(const QString &key, const QVariant &value) const;

  /**
   * @brief Returns a QVariantMap object that contains the specified key, value, and
   * additional value.
   * @param key The name of the key.
   * @param value The value associated with the key.
   * @param addtValue The additional value associated with the key.
   * @return A QVariantMap object that contains the key, value, and additional
   * value.
   */
  QVariantMap getObject(const QString &key, const QVariant &value,
                        const QVariant &addtValue) const noexcept;

  /**
   * @brief Parses the given QVariant data and extracts objects based on the provided
   * parameters.
   * @param data The QVariant data to parse.
   * @param params The QMap of parameters used to filter the objects.
   * @tparam T Can be equal QString or int.
   * @return A QVariantMap containing the parsed objects.
   */
  template <typename T>
  QVariantMap parseObjects(const QVariant &data,
                           const QMap<QString, QString> params) const noexcept;

  /**
   * @brief Get note details parameters.
   * Returns a QMap<QString, QString> object containing the parameters for
   * emotions categories.
   * @return A QMap<QString, QString> object representing the parameters. The
   * keys are the emot category names (angry, sad, fear, happy, love) and the
   * values are the corresponding parameter names (":angryLevel", :sadLevel",
   * ":fearLevel", ":happyLevel", ":loveLevel").
   */
  QMap<QString, QString> getEmotCtgParameters() const;

  /**
   * @brief Get note details parameters.
   * Returns a QMap<QString, QString> object containing the parameters for
   * retrieving note details.
   * @return A QMap<QString, QString> object representing the parameters. The
   * keys are the note details (body, behavior, thoughts, situation) and the
   * values are the corresponding parameter names (":body", ":behavior",
   * ":thoughts", ":situation").
   */
  QMap<QString, QString> getNoteDetailsParameters() const;

  /**
   * @brief Executes a SQL script and returns the result.
   * @param script The SQL script to execute.
   * @return True if the query is executed successfully, false otherwise.
   */
  bool execQuery(const QString &script);

  /**
   * @brief Executes a list of SQL scripts and returns whether all queries were
   * successful.
   * @param scripts A QStringList of SQL scripts to execute
   * @return `true` if all queries were successful, `false` otherwise
   */
  bool execQuery(const QStringList &query);

  /**
   * @brief Inserts a query template into the NoteStorage.
   * @param script The script to prepare the query
   * @param bindings The map of bindings for the query
   * @param lastId The variable to store the last insert ID. In these variable
   * will be wrote the last insert ID
   */
  void insertQueryTempl(const QString &script, const QVariantMap &bindings,
                        int &lastId);

  /**
   * @brief Executes a select query on the database using the provided script
   * and process function.
   * @param query The QSqlQuery for execute.
   * @param process The auto function to process the query results
   * @return A boolean indicating the success of the query execution
   */
  bool execSelectQuery(QSqlQuery &query, const auto &process);

  /**
   * @brief Executes a select query on the database using the provided script
   * and process function.
   * @param script The QString containing the query script
   * @param process The auto function to process the query results
   * @return A boolean indicating the success of the query execution
   */
  bool execSelectQuery(const QString &script, const auto &process);

  /**
   * @brief Executes a select query with a given script, process, and bindings.
   * @param script The SQL script to execute
   * @param process The process to apply to the query result
   * @param bindings The map of bindings for the query
   * @return `true` if the select query is successfully executed, `false` otherwise
   */
  bool execSelectQueryTempl(const QString &script, const auto &process,
                            const QVariantMap &bindings);

  /**
   * @brief Parses and executes insert queries for an object based on its type.
   * @param type The type of the object to be parsed and executed.
   * @param object The object to be parsed and executed.
   * @param params Additional parameters for parsing and executing the object.
   * @param additionalObject An additional object to be used during parsing and
   * executing.
   */
  void parseAndInsertObject(NoteStorage::ObjectCtgTypes type,
                            const QVariant &object = {},
                            const QMap<QString, QString> &params = {},
                            const QVariant &additionalObject = {});

  /**
   * @brief Logs a message with the specified type and source location.
   * @param message the message to be logged
   * @param type the type of the log message (default: QtDebugMsg)
   * @param location the source location where the log message originated
   * (default: srcLoc::current())
   * @throws None
   */
  inline void logMessage(
      const auto &message, QtMsgType type = QtDebugMsg,
      const std::source_location &location = srcLoc::current()) const noexcept {
    QDebug(type) << QString(location.function_name()) + ":" << message;
  }
};

template <typename T>
QVariantMap
NoteStorage::parseObjects(const QVariant &data,
                          const QMap<QString, QString> params) const noexcept {
  QJsonArray arrayObjects{data.toJsonArray()};
  // Function `toJsonArray` can return different results. It can be array or
  // nested array.
  if (arrayObjects[0].isArray()) {
    arrayObjects = arrayObjects[0].toArray();
  }

  QVariantMap bindings;
  for (const QJsonValue &item : arrayObjects) {
    const QJsonObject obj{item.toObject()};
    const QString objName{obj.value("name").toString()};
    if (const auto it = params.find(objName); it != params.end()) {
      if constexpr (std::is_same<T, QString>()) {
        bindings.insert({{it.value(), obj.value("value").toString()}});
      } else {
        bindings.insert({{it.value(), obj.value("value").toInt()}});
      }
    } else {
      logMessage("Key not found:" + objName + QJsonDocument(obj).toJson());
    }
  }

  return bindings;
}
