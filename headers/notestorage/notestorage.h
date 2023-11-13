#pragma once
#include <objectbox.hpp>
#include <QObject>
#include <QtQuick>

class NoteStorage : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit NoteStorage(QObject *parent = nullptr);

signals:
};
