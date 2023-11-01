import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Felgo

Item {
    id: root
    implicitHeight: 200
    implicitWidth: 300

    property var emotCategories: {
        "Angry": {
            "1": true,
            "2": false,
            "3": false
        },
        "Fear": {
            "4": false,
            "5": false,
            "6": false
        },
        "Sad": {
            "7": false,
            "8": false,
            "9": false
        },
        "Love": {
            "10": false,
            "11": false,
            "12": false
        },
        "Happy": {
            "13": false,
            "14": false,
            "15": false
        }
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        property int lineHeight: 30
        columns: 4

        AppText {
            text: "Angry"
            id: labelAngry
        }
        AppCheckBox {
            text: "1"
            checked: emotCategories[labelAngry.text][text]
            onCheckedChanged: {
                emotCategories[labelAngry.text][text] = false
                console.log(emotCategories[labelAngry.text][text])
            }
        }
        AppCheckBox {
            text: "2"
        }
        AppCheckBox {
            text: "3"
        }

        AppText {
            text: "Fear"
        }
        AppCheckBox {
            text: "1"
        }
        AppCheckBox {
            text: "2"
        }
        AppCheckBox {
            text: "3"
        }

        AppText {
            text: "Sad"
        }
        AppCheckBox {
            text: "1"
        }
        AppCheckBox {
            text: "2"
        }
        AppCheckBox {
            text: "3"
        }

        AppText {
            text: "Happy"
        }
        AppCheckBox {
            text: "1"
        }
        AppCheckBox {
            text: "2"
        }
        AppCheckBox {
            text: "3"
        }

        AppText {
            text: "Love"
        }
        AppCheckBox {
            text: "1"
        }
        AppCheckBox {
            text: "2"
        }
        AppCheckBox {
            text: "3"
        }
    }
}
