import Felgo
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "pages"

App {
    id: root

  // Height and width for desktop app.
  height: 640
  width: 480
  NavigationStack {
    MainPage {}
  }
}
