import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
    id: root
    implicitHeight: 200
    implicitWidth: 300

    property var emotCategories: [
        {"name": qsTr("Angry")}, {"name": qsTr("Fear")},
        {"name": qsTr("Sad")}, {"name": qsTr("Love")},
        {"name": qsTr("Happy")}
    ]

    JsonListModel {
        id: listModel
        source: emotCategories
    }

    ColumnLayout {
        anchors.fill: parent

        AppText {
            id: emotLabel
            text: qsTr("What are you feel?")
            Layout.alignment: Qt.AlignCenter
        }

        AppListView {
            id: emotSelector
            model: listModel

            delegate: Item {
                Row {

                    Text {
                        text: model.name
                    }

                    Repeater {
                        model: 4
                        delegate: Rectangle {
                            height: 30
                            width: 30
                            border.width: 1
                        }
                    }
                }
            }
        }
    }
}


