#pragma once
#include "constants.hpp"
#include <QDateTime>
#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>
#include <QtQuick>
#include <database/database.obx.hpp>
#include <database/objectbox-model.h>
#include <objectbox.hpp>
#include <utility>
#include <functional>
#include <cstdint>

namespace emt = constants::emotions;
namespace quest = constants::questionsLabels;

class NoteStorage : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit NoteStorage(QObject *parent = nullptr);
  Q_INVOKABLE QVector<QVariant> getNoteList();
  Q_INVOKABLE QVariantMap getNoteDetails(const obx_id &noteId) const;
  Q_INVOKABLE QVariantMap getDefaultNote() const;
  Q_INVOKABLE short getDefaultNoteId();
  Q_INVOKABLE void addNewNote(const int &id, const QVariant &note);

  

  private:
  std::unique_ptr<obx::Box<Note>> mNoteBase;
  std::unique_ptr<obx::Box<NoteText>> mNoteDetailsBase;
  std::unique_ptr<obx::Store> mStore;
  obx_id mIdDefaultNote;

  QVector<QVariant> prepareEmotObject(const std::unique_ptr<Note> &note) const;
  QVector<QVariant>
  prepareTextObject(const std::unique_ptr<NoteText> &note) const;
  QVariantMap getObject(const QString &key, const QVariant &value) const;
  QVariantMap getObject(const QString &key, const QVariant &value,
                        const QVariant &addtValue) const;
  std::unique_ptr<Note> getEmptyNote() const;
  std::unique_ptr<NoteText> getEmptyNoteDetails() const;
  
  void parseEmotCtg(const QVariant &data, Note &note);
};
