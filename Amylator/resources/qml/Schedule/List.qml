import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml.Models 2.1
import "../Widgets" as Widgets 


Rectangle {
    id: root

    property int editIndex: 0
    property int editTemp: 0
    property int editDur: 0
    property int currentStep: -1

    signal editClicked

    onCurrentStepChanged: console.log("step = " + currentStep)
    //---------------------------------------------------------------------
    
    Component {
        id: cellView 

        Rectangle {
            id: cellBackground
            width: root.width
            height: 40
            color: (root.currentStep === index) ? "gray" : "white"
            Text { 
                id: indexText
                anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
                anchors { leftMargin: 3; topMargin: 2 }
                width: 20
                text: index
                font { bold: true; pixelSize: 20 }
            }
            Column {
                id: column
                anchors { 
                    left: indexText.right
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right 
                }

                Text { text: '<b>Duration:</b> </b>' + duration + ' min' }
                Text { text: '<b>Temperature:</b> ' + temperature + ' °C' }
            }
            Widgets.EditButton {
                id: editBtn
                anchors { right: parent.right; rightMargin: 8 }
                anchors.verticalCenter: parent.verticalCenter
                onClicked: { 
                    root.editIndex = index; 
                    root.editTemp = temperature; 
                    root.editDur = duration; 
                    editClicked() 
                }
            }
            Rectangle {
                color: "black"
                anchors { bottom: parent.bottom; left: parent.left; right: parent.right }
                height: 1
            }
        }
    }

    //---------------------------------------------------------------------

    ListView {
        id: stepsList 
        anchors.fill: parent
        model: dataSource.entries 
        delegate: cellView 
    }
}
