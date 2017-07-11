import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import BrewComponent 1.0 as BC
import "./Schedule" as Schedule 


Window {
    id: mainWindow
    title:   "Brew Control"
    visible: true
    color:   "black"

    width:   1000
    height:  600
    minimumHeight: 400
    minimumWidth:  800

    //---------------------------------------------------------------------

    //AppMenu           { id: appMenu }
    BC.Amylator { 
        id: amylator 
    }

    //---------------------------------------------------------------------

    Schedule.Schedule {
        id: schedule
        width: 250
        anchors { top: header.bottom; left: parent.left; bottom: logging.top }
        anchors.topMargin: 12
        anchors.bottomMargin: 6

        dataSource:     amylator.scheduleData
        currentStep:    amylator.currentStep
    }

    Logging {
        id: logging
        height: 200
        width: schedule.width
        anchors { left: parent.left; bottom: parent.bottom }
    }

    Plot {
        id: plot
        anchors.top:    header.bottom
        anchors.bottom: parent.bottom
        anchors.right:  parent.right
        anchors.left:   schedule.right

        dataSource:     amylator.plotData
    }

    //---------------------------------------------------------------------

    Network {
        id: networkView
        anchors { left: parent.left; right: parent.right; top: header.bottom; bottom: parent.bottom }
        network: amylator.client
    }

    //---------------------------------------------------------------------

    About {
        id: aboutView
        anchors { left: parent.left; right: parent.right; top: header.bottom; bottom: parent.bottom }

        version: amylator.version
    }

    //---------------------------------------------------------------------

    Header {
        id: header
        anchors { left: parent.left; right: parent.right; top: parent.top }
        connected: amylator.client.connected
        running: amylator.running

        onConnectionClicked: networkView.visible = !networkView.visible
        onReloadClicked:     amylator.reload()
        onAboutClicked:      aboutView.visible = !aboutView.visible

        onStartClicked:      { amylator.client.connected ? amylator.start() : startError.visible = true }
        onStopClicked:       stopRequest.visible = true
        onPauseClicked:      amylator.pause()
    }

    MessageDialog {
        id: startError 
        title: "Starting failed!"
        text:  "Can't start mashing. There is no connection to the server."
        icon: StandardIcon.Critical
        visible: false
        onAccepted: visible = false
    }

    MessageDialog {
        id: stopRequest 
        icon: StandardIcon.Question
        title: "Stop mashing?"
        text:  "Do you realy want to stop?"
        visible: false
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: { amylator.stop(); visible = false; }
        onNo:  { visible = false; }
    }
}
