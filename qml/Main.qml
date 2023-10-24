import Felgo
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

App {
    id: root

    // Height and width for desktop app.
    //    height: 640
    //    width: 480
    Material.theme: Material.Dark
    Material.accent: Material.Purple

    NavigationStack {
        AppPage {
            id: mainPage
            title: "PsyNote"

            GridLayout {
                height: parent.height * 0.5
                width: parent.width
                columns: 3

                property int minSize: 100
                property int marginsCells: 10
                property int buttonRadius: 20

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    radius: parent.buttonRadius

                    text: qsTr("Diary")
                }

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    radius: parent.buttonRadius

                    text: qsTr("Chat")
                }

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    text: qsTr("Results")

                    radius: parent.buttonRadius
                }

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    text: qsTr("Tests")

                    radius: parent.buttonRadius
                }
            }
        }
    }
}
