import Felgo
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

App {
    id: root

    // Height and width for desktop app.
    //    height: 640
    //    width: 480

    MainPage {
        diaryPage: appDiaryPage
        chatPage: appChatPage
        testsPage: appTestPage
        resultsPage: appResultsPage

    }

    Component {
        id: appDiaryPage
        DiaryPage{}
    }

    Component {
        id: appTestPage
        TestsPage {}
    }

    Component {
        id: appResultsPage
        ResultsPage {}
    }

    Component {
        id: appChatPage
        ChatPage{}
    }
}
