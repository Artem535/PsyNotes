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

namespace emt = constants::emotions;

class NoteStorage : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit NoteStorage(QObject *parent = nullptr);
  Q_INVOKABLE QVector<QVariant> getNoteList();
  Q_INVOKABLE QVariantMap getNoteDetails(const obx_id &noteId) const;
  Q_INVOKABLE QVariantMap getDefaultNote() const;

private:
  std::unique_ptr<obx::Box<Note>> mNoteBase;
  std::unique_ptr<obx::Box<NoteText>> mNoteDetailsBase;
  std::unique_ptr<obx::Store> mStore;
  obx_id mIdDefaultNote;

  QVector<QVariant> prepareEmotObject(const std::unique_ptr<Note> &note) const;
  std::unique_ptr<Note> getEmptyNote() const;
};
