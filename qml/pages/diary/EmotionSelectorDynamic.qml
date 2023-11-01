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
                      "name": "2",
                      "selected": false
                  }, {
                      "name": "3",
                      "selected": false
                  }],
        "Fear": [{
                     "name": "4",
                     "selected": false
                 }, {
                     "name": "5",
                     "selected": false
                 }, {
                     "name": "6",
                     "selected": false
                 }],
        "Sad": [{
                    "name": "7",
                    "selected": false
                }, {
                    "name": "8",
                    "selected": false
                }, {
                    "name": "9",
                    "selected": false
                }],
        "Love": [{
                     "name": "10",
                     "selected": false
                 }, {
                     "name": "11",
                     "selected": false
                 }, {
                     "name": "12",
                     "selected": false
                 }],
        "Happy": [{
                      "name": "13",
                      "selected": false
                  }, {
                      "name": "14",
                      "selected": false
                  }, {
                      "name": "15",
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
