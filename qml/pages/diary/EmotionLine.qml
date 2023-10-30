import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
    id: root
    implicitHeight: 30
    implicitWidth: 100
    property alias emotName: item.text
    property alias emotArray: jsonModel.source

    AppListItem {
        id: item
        anchors.fill: parent
        showDisclosure: false
        text: ""

        JsonListModel {
            id: jsonModel
            source: []
        }

        rightItem: Repeater {
            model: jsonModel
            delegate: AppCheckBox {
                text: model.name
                state: model.selected
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
