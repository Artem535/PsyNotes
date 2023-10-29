import QtQuick
import Felgo

AppPage {
    title: "Diary"
    property var notes: [
        { "title": "some title",
            "day": "28.10.23",
            "time": "13:13",
            "text": "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeext"
        }
    ]

    AppListView {
        model: notes
        section.property: "day"

        delegate: AppListItem {
            rightText: modelData.time
            text: modelData.title
            detailText: modelData.text
            onSelected: {
                navigationStack.push(notePage)
            }
        }
    }

    FloatingActionButton {
        iconType: IconType.plus
        visible: true
    }

    Component {
        id: notePage
        NotePage {

        }
    }

  }

