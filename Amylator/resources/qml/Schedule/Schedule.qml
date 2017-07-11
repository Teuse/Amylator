import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml.Models 2.1


Rectangle {
    id: root 

    property var dataSource
    property int currentStep: -1

    color: "black"

    //---------------------------------------------------------------------
    
    List {
        id: scheduleList
        anchors.top: scheduleHeader.bottom
        anchors.topMargin: 4
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onEditClicked: addStep.editStep(editIndex, editDur, editTemp)

        currentStep: root.currentStep
    }

    //---------------------------------------------------------------------
    
    Header {
        id: scheduleHeader
        anchors { top: parent.top; left: parent.left; right: parent.right }
        onPlusClicked:  addStep.addStep() 
        onClearClicked: dataSource.clear()
    }

    //---------------------------------------------------------------------
    
    AddStep {
        id: addStep
        visible: false
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        onCanceled: addStep.visible = false
        onAccepted: {
            if (!isEdit)  dataSource.add(duration, temperature)
            else          dataSource.edit(index, duration, temperature)
            addStep.visible = false
        }
    }
}
