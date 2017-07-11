import QtQuick 2.0
import QtCharts 2.1
import QtGraphicalEffects 1.0
import './Widgets' as Widget
import './Definitions'


Rectangle {
    id: header 

    property bool connected: false 
    property bool running: false 
    property bool stopped: false 

    signal connectionClicked
    signal reloadClicked
    signal aboutClicked

    signal startClicked
    signal stopClicked
    signal pauseClicked

    //---------------------------------------------------------------------
    
    height: 35 

    //---------------------------------------------------------------------
    
    LinearGradient {
        anchors.fill: parent
        start:  Qt.point(0, 0)
        end:    Qt.point(0, 33)
        gradient: Gradient {
            GradientStop { position: 0.0; color: Color.orange }
            GradientStop { position: 1.0; color: Color.orangeDark }
        }
    }

    //---------------------------------------------------------------------

    Rectangle {
        id: transport
        width: 100; height: 25
        anchors { top: parent.top; topMargin: 4 }
        anchors.horizontalCenter: parent.horizontalCenter
        color: "black"
        radius: 2
     
        Widget.StopButton {
            id: stopBtn
            anchors { verticalCenter: parent.verticalCenter; right: playBtn.left; rightMargin: 8 }
            onClicked: stopClicked()
        }
        Widget.PlayButton {
            id: playBtn
            anchors { verticalCenter: parent.verticalCenter; right: transport.right; rightMargin: 8 }
            onClicked: startClicked()
            highlighted: header.running
        }
    }

    //---------------------------------------------------------------------

    Image {
        id: connectionImg 
        width: 25; height: 25
        anchors { right: parent.right; rightMargin: 20; top: parent.top; topMargin: 4 }
        source: header.connected ? "../../images/header/connection_on.png" : "../../images/header/connection_off.png"
        MouseArea {
            id: connectionBtn
            anchors.fill: parent 
            onClicked: connectionClicked()
        }
    }

    Image {
        id: reloadImg 
        width: 23; height: 23
        anchors { right: connectionImg.left; rightMargin: 15; top: parent.top; topMargin: 5 }
        source: "../../images/header/reload.png"
        MouseArea {
            id: reloadBtn
            anchors.fill: parent 
            onClicked: reloadClicked()
        }
    }

    //---------------------------------------------------------------------

    Image {
        id: maltImg 
        anchors { left: parent.left; leftMargin: 20; top: parent.top; topMargin: 4 }
        source: "../../images/header/malt.png"
    }

    Text {
        id: bcText 
        text: "Brew Control"
        height: parent.height - bottomShadow.height
        font { pixelSize: 30; bold: true; family: "Chalkboard" }
        anchors { left: maltImg.right; leftMargin: 5; top: parent.top; topMargin: -3 }
    }
    
    MouseArea {
        id: maltBtn
        anchors { top: maltImg.top; bottom: maltImg.bottom; left: maltImg.left; right: bcText.right } 
        onClicked: aboutClicked()
    }

    //---------------------------------------------------------------------

    Rectangle {
        id: bottomShadow
        color: "black"
        height: 2 
        anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
    }

}
