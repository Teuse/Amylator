import QtQuick 2.0
import QtGraphicalEffects 1.0
import '../Definitions'

Rectangle {
    id: header 

    signal plusClicked 
    signal clearClicked 

    property string text: "blub"

    //---------------------------------------------------------------------

    radius: 3
    height: 35 
    clip: true
    color: Color.headerGrayBright

    // LinearGradient {
    //     anchors.fill: parent
    //     source: header
    //     start:  Qt.point(0, 0)
    //     end:    Qt.point(0,header.height)
    //     gradient: Gradient {
    //         GradientStop { position: 0.0; color: Color.headerGrayBright }
    //         GradientStop { position: 1.0; color: Color.headerGrayDark }
    //     }
    // }

    Text { 
        text: header.text
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font { pixelSize: 15; bold: true }
    }
}
