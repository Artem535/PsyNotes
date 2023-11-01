import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
    id: root
    implicitHeight: 30
    implicitWidth: 100
    property alias emotName: item.text
    property var emotArray: []

    AppListItem {
        id: item
        anchors.fill: parent
        showDisclosure: false
        text: ""

        JsonListModel {
            id: jsonModel
            source: emotArray
        }

        rightItem: Row {
            width: item.width * 0.5
            height: item.height
            Repeater {
                model: jsonModel
                delegate: AppCheckBox {
                    width: parent.width / 3
                    text: model.name
                    checked: model.selected
                    anchors.verticalCenter: parent.verticalCenter
                    onCheckedChanged: {
                        var index = jsonModel.indexOf("name", model.name)
                        emotArray[index]["selected"] = checked
                    }
                }
            }
        }
    }
}
