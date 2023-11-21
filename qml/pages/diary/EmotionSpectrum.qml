import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
  id: root
  implicitHeight: 200
  implicitWidth: 300

  property alias emotCategories: jsonModel.source

  function syncModeToValue() {
    jsonModel.syncModelToSource()
  }

  JsonListModel {
    id: jsonModel
    source: emotCategories
  }

  ColumnLayout {
    anchors.fill: parent
    property int lineHeight: 30

    AppText {
      id: emotLabel
      text: qsTr("What are you feel?")
      Layout.alignment: Qt.AlignCenter
      Layout.preferredHeight: parent.height * 0.05
    }

    Repeater {
      model: jsonModel
      delegate: EmotionLine {
        Layout.fillWidth: true
        emotName: model.name
        emotValue: model.value
        onEmotValueChanged: {
          jsonModel.setProperty(index, "value", emotValue)
        }
      }
    }
  }
}
