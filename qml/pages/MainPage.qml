import QtQuick
import Felgo
import QtQuick.Layouts 1.15
import "diary"

AppPage {
    id:root

    property var diaryPage
    property var chatPage
    property var resultsPage
    property var testsPage

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

                    onClicked: mainPage.navigationStack.push(diaryPage)
                }

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    radius: parent.buttonRadius

                    text: qsTr("Chat")

                    onClicked: mainPage.navigationStack.push(chatPage)
                }

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    text: qsTr("Results")

                    radius: parent.buttonRadius

                    onClicked: mainPage.navigationStack.push(resultsPage)
                }

                AppButton {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumWidth: parent.minSize
                    Layout.minimumHeight: parent.minSize

                    Layout.margins: parent.marginsCells

                    text: qsTr("Tests")

                    radius: parent.buttonRadius

                    onClicked: mainPage.navigationStack.push(testsPage)
                }
            }
        }
    }

}
