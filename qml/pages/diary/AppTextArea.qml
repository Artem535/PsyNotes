import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Felgo

Item {
  id: root
  implicitHeight: 300
  implicitWidth: 200

  property alias title: areaTitle.text
  property alias text: areaText.text

  ColumnLayout {
    anchors.fill: root

    AppText {
      id: areaTitle
      Layout.alignment: Qt.AlignCenter
      Layout.preferredHeight: root.height * 0.05
    }

    Frame {
      Layout.fillWidth: true
      Layout.fillHeight: true
      anchors.margins: 10

      AppTextEdit {
        id: areaText
        anchors.fill: parent
        wrapMode: TextEdit.Wrap
        placeholderText: "This field is optional."
      }
    }
  }
}
