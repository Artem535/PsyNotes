import QtQuick
import Felgo
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AppPage {
  id: root
  title: "ChatPage"
  readonly property string url: ""
  property var exampleModel: [{
      "user": true,
      "msg": "example text",
      "time": "14:00"
    },
    {
      "user": true,
      "msg": "Long line".repeat(15) ,
      "time": "14:00"
    },

    {
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
      model: jsonListModel
      Layout.fillWidth: true
      Layout.fillHeight: true
      spacing: 10

      delegate: Rectangle {
        id: msgBackground
        color: "#e4dddd"

        readonly property double maxWidth: 0.8 * parent.width

        width: msgText.contentWidth < maxWidth ? msgText.contentWidth : maxWidth
        height: msgText.contentHeight

        anchors.left: model.user ? undefined : parent.left
        anchors.right: model.user ? parent.right : undefined

        radius: 10

        AppText {
          id: msgText
          width: parent.maxWidth
          text: model.msg
          wrapMode: Text.WordWrap
        }

      }


    }

    Rectangle {
      id: msgInputBackground
      Layout.fillWidth: true
      Layout.preferredHeight: 0.1 * parent.height
      Layout.margins: dp(10)
      Layout.maximumHeight: dp(40)
      color: "#d7d7d7"
      border.color: "#a6a6a6"
      radius: 30

      RowLayout {
        anchors.fill: parent
        anchors.leftMargin: dp(12)
        anchors.rightMargin: dp(5)

        AppTextField {
          id: msgInput
          Layout.preferredWidth: parent.width - sendMsgbutton.width
          // ARGB fully transparent
          backgroundColor: "#00000000"
        }

        AppButton {
          id: sendMsgbutton
          minimumHeight: dp(10)
          minimumWidth: dp(10)
          Layout.fillHeight: true
          Layout.preferredWidth: sendMsgbutton.height
          horizontalMargin: verticalMargin
          iconType: IconType.paperplane
          radius: sendMsgbutton.width / 2
          onClicked: {
            exampleModel.push({
                                "user": true,
                                "msg": "example text",
                                "time": "14:00"
                              })
            root.exampleModelChanged()
          }
        }
      }
    }
  }
}
