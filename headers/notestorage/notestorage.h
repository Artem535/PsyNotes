#pragma once
#include <QObject>
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

signals:

private:
  std::unique_ptr<obx::Box<Note>> mNoteBase;
};
