import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
  id: root
  implicitHeight: 30
  implicitWidth: 100
  property alias emotName: emotName.text
  property alias emotValue: slider.value

  ColumnLayout {
    anchors.fill: parent
    AppText {
      id: emotName
      text: "NOT SET"
      Layout.alignment: Qt.AlignCenter
    }

    AppSlider {
      id: slider
      value: 0
      from: 0
      to: 5
      stepSize: 1
      snapMode: "SnapOnRelease"
      Layout.fillWidth: true
    }
  }
}
