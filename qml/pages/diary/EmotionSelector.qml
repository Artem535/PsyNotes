import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
    id: root
    implicitHeight: 200
    implicitWidth: 300

    property var emotCategories: {
        "Angry": [{
                      "name": "1",
                      "selected": false
                  }, {
                      "name": "1",
                      "selected": false
                  }],
        "Fear": [{
                     "name": "2",
                     "selected": false
                 }],
        "Sad": [{
                    "name": "3",
                    "selected": false
                }],
        "Love": [{
                     "name": "4",
                     "selected": false
                 }],
        "Happy": [{
                      "name": "5",
                      "selected": false
                  }]
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

        EmotionLine {
            Layout.fillWidth: true
            Layout.fillHeight: true
            emotName: "Angry"
            emotArray: emotCategories[emotName]
        }

        EmotionLine {
            Layout.fillWidth: true
            Layout.fillHeight: true
            emotName: "Fear"
            emotArray: emotCategories[emotName]
        }

        EmotionLine {
            Layout.fillWidth: true
            Layout.fillHeight: true
            emotName: "Sad"
            emotArray: emotCategories[emotName]
        }

        EmotionLine {
            Layout.fillWidth: true
            Layout.fillHeight: true
            emotName: "Happy"
            emotArray: emotCategories[emotName]
        }

        EmotionLine {
            Layout.fillWidth: true
            Layout.fillHeight: true
            emotName: "Love"
            emotArray: emotCategories[emotName]
        }
    }
}
