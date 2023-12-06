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

namespace emt = constants::emotions;
namespace quest = constants::questionsLabels;
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
  int mLastTextId = constants::database::defaultNoteID;
  int mLastEmotId = constants::database::defaultNoteID;
  int mLastNoteId = -1;
  QSqlDatabase mSqlNoteBase;

  int mIdDefaultNote;

  /**
   * @brief
   *
   * @param note
   * @return QVector<QVariant>
   */
  QVector<QVariant> prepareEmotObject(const QSqlQuery &query) const;

  /**
   * @brief
   *
   * @param note
   * @return QVector<QVariant>
   */
  QVector<QVariant> prepareTextObject(const QSqlQuery &query) const;

  /**
   * @brief Get the Object object
   *
   * @param key
   * @param value
   * @return QVariantMap
   */
  QVariantMap getObject(const QString &key, const QVariant &value) const;

  /**
   * @brief Get the Object object
   *
   * @param key
   * @param value
   * @param addtValue
   * @return QVariantMap
   */
  QVariantMap getObject(const QString &key, const QVariant &value,
                        const QVariant &addtValue) const;

  /**
   * @brief
   *
   * @param data
   * @param note
   */
  template <typename T>
  QVariantMap parseObjects(const QVariant &data,
                           const QMap<QString, QString> params) const noexcept;

  /**
   * @brief Get the Emot Ctg Map object
   *
   * @param note
   * @return QMap<QString, std::reference_wrapper<int8_t>>
   */
  QMap<QString, QString> getEmotCtgParameters() const;

  /**
   * @brief Get the Note Details Map object
   *
   * @param note
   * @return QMap<QString, std::reference_wrapper<std::string>>
   */
  QMap<QString, QString> getNoteDetailsParameters() const;

  bool execQuery(const QString &script);

  bool execQuery(const QStringList &query);

  void insertQueryTempl(const QString &script, const QVariantMap &bindings,
                        int &lastId);

  // template<class QueryHandler>
  bool execSelectQuery(QSqlQuery &query, const auto &process);

  // template<class QueryHandler>
  bool execSelectQuery(const QString &script, const auto &process);

  bool execSelectQueryTempl(const QString &script, const auto &process,
                            const QVariantMap &bindings);

  inline void logMessage(
      const QString &message, QtMsgType type = QtDebugMsg,
      const std::source_location &location = srcLoc::current()) const noexcept {
    QDebug(type) << QString(location.function_name()) + ":" + message;
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
