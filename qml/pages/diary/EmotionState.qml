import QtQuick
import Felgo
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    implicitHeight: 30
    implicitWidth: 300

    property alias from: emotSlider.from
    property alias to: emotSlider.to

    ColumnLayout {
        id: layout
        anchors.fill: parent

        AppText {
            id: emotLabel
            text: qsTr("How are you?")
            Layout.alignment: Qt.AlignCenter
        }

        AppSlider {
            id: emotSlider
            from: -3
            to: 3
            stepSize: 1
            snapMode: Slider.SnapOnRelease
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 0.8 * parent.width
        }
    }
}
