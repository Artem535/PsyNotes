import Felgo
import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "diary"
import "chat"
import "results"
import "tests"
import "../logic"

AppPage {
  id: root

  TabControl {
    tabPosition: TabBar.Footer
    tabBar.currentIndex: 1

    NavigationItem {
      id: appChatPage
      title: qsTr("CHAT")
      ChatPage {}
    }

    NavigationItem {
      id: appDiaryPage
      title: qsTr("DIARY")
      DiaryPage {}
      onSelected: {
        logic.fetchNoteData()
      }
    }

    NavigationItem {
      id: appResultsPage
      title: qsTr("RESULTS")
      ResultsPage {}
    }

    NavigationItem {
      id: appTestsPage
      title: qsTr("TEST")
      TestsPage {}
    }
  }

  Logic {
    id: logic
  }
}
