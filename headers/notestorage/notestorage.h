#pragma once
#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QtQuick>
#include <database/database.obx.hpp>
#include <database/objectbox-model.h>
#include <objectbox.hpp>
#include <utility>

class NoteStorage : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit NoteStorage(QObject *parent = nullptr);
  Q_INVOKABLE QVariantList getNoteList();

private:
  std::unique_ptr<obx::Box<Note>> mNoteBase;
  std::unique_ptr<obx::Store> mStore;
};
