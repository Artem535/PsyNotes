#pragma once
#include "constants.hpp"
#include <QDateTime>
#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>
#include <QtQuick>
#include <cstdint>
#include <database/database.obx.hpp>
#include <database/objectbox-model.h>
#include <functional>
#include <memory>
#include <objectbox.hpp>
#include <utility>

namespace emt = constants::emotions;
namespace quest = constants::questionsLabels;
namespace noteDetails = constants::noteDetails;

class NoteStorage : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit NoteStorage(QObject *parent = nullptr);
  Q_INVOKABLE QVector<QVariant> getNoteList();
  Q_INVOKABLE QVariant getNote(const obx_id &id);
  Q_INVOKABLE QVariantMap getNoteDetails(const obx_id &noteId) const;
  Q_INVOKABLE QVariantMap getDefaultNote() const;
  Q_INVOKABLE short getDefaultNoteId();
  Q_INVOKABLE obx_id addNewNote(const obx_id &id, const QVariant &note);

private:
  std::unique_ptr<obx::Box<Note>> mNoteBase;
  std::unique_ptr<obx::Box<NoteText>> mNoteDetailsBase;
  std::unique_ptr<obx::Store> mStore;
  obx_id mIdDefaultNote;

  /**
   * @brief
   *
   * @param note
   * @return QVector<QVariant>
   */
  QVector<QVariant> prepareEmotObject(const std::unique_ptr<Note> &note) const;

  /**
   * @brief
   *
   * @param note
   * @return QVector<QVariant>
   */
  QVector<QVariant>
  prepareTextObject(const std::unique_ptr<NoteText> &note) const;

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
   * @brief Get the Empty Note object
   *
   * @return std::unique_ptr<Note>
   */
  std::unique_ptr<Note> getEmptyNote() const;

  /**
   * @brief Get the Empty Note Details object
   *
   * @return std::unique_ptr<NoteText>
   */
  std::unique_ptr<NoteText> getEmptyNoteDetails() const;

  /**
   * @brief
   *
   * @param data
   * @param note
   */
  template <typename T>
  void parseObjects(const QVariant &data,
                    QMap<QString, std::reference_wrapper<T>> objectsRef);

  /**
   * @brief Get the Emot Ctg Map object
   *
   * @param note
   * @return QMap<QString, std::reference_wrapper<int8_t>>
   */
  QMap<QString, std::reference_wrapper<int8_t>> getEmotCtgMap(Note &note);

  /**
   * @brief Get the Note Details Map object
   *
   * @param note
   * @return QMap<QString, std::reference_wrapper<std::string>>
   */
  QMap<QString, std::reference_wrapper<std::string>>
  getNoteDetailsMap(NoteText &note);

  QVariant createShortNote(const Note &note);
};

template <typename T>
inline void
NoteStorage::parseObjects(const QVariant &data,
                          QMap<QString, std::reference_wrapper<T>> objectsRef) {
  QJsonArray arrayObjects{data.toJsonArray()};
  // Function `toJsonArray` can return different results. It can be array or
  // nested array.
  if (arrayObjects[0].isArray()) {
    arrayObjects = arrayObjects[0].toArray();
  }

  for (const QJsonValue &item : arrayObjects) {
    const QJsonObject obj{item.toObject()};
    const QString objName{obj["name"].toString()};
    if (auto it = objectsRef.find(objName); it != objectsRef.end()) {
      if constexpr (std::is_same<T, int8_t>())
        it->get() = static_cast<T>(obj["value"].toInt());
      else
        it->get() = obj["value"].toString().toStdString();
    }
  }
}
