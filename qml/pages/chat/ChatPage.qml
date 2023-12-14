import QtQuick
import Felgo
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AppPage {
  title: "ChatPage"
  property var exampleModel: [{
      "user": true,
      "msg": "example text",
      "time": "14:00"
    }, {
      "user": false,
      "msg": "Ai text",
      "time": "14:00"
    }]

  JsonListModel {
    id: jsonListModel
    source: exampleModel
  }

  ColumnLayout {
    anchors.fill: parent
    AppListView {
      Layout.fillWidth: true
      Layout.fillHeight: true
      model: jsonListModel
      delegate: SimpleRow {
        text: model.user ? "User: " + model.msg : "Ai: " + model.msg
      }
    }

    Rectangle {
      id: chatInputBackground
      Layout.fillWidth: true
      Layout.preferredHeight: 0.1 * parent.height
      Layout.margins: dp(10)
      Layout.maximumHeight: dp(40)
      color: "#d7d7d7"
      border.color: "#a6a6a6"
      radius: 30

      RowLayout {
        anchors.fill: parent
        //        anchors.topMargin: 2
        anchors.leftMargin: dp(12)
        anchors.rightMargin: dp(5)

        //        anchors.bottomMargin: 2
        AppTextField {
          id: textInput
          Layout.preferredWidth: parent.width - appButton.width
          backgroundColor: chatInputBackground.color
        }

        AppButton {
          id: appButton
          minimumHeight: dp(10)
          minimumWidth: dp(10)
          Layout.fillHeight: true
          Layout.preferredWidth: appButton.height
          horizontalMargin: verticalMargin
          iconType: IconType.paperplane
          radius: appButton.width / 2 // Сделаем радиус половиной ширины кнопки
        }
      }
    }
  }
}
