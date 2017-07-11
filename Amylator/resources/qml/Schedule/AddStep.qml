import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2


Rectangle {
    id: addView 

    signal canceled
    signal accepted

    property int minTemperature: 30
    property int maxTemperature: 100

    property int minDuration: 10
    property int maxDuration: 90

    property int index: -1
    readonly property bool isEdit: index >= 0 
    readonly property int duration:    parseInt( durationText.text )
    readonly property int temperature: parseInt( temperatureText.text )

    //---------------------------------------------------------------------

    function addStep() {
        addView.visible = true;
        addView.index = -1;
        durationText.text = "";
        temperatureText.text = "";
        headline.text = "Add mash step";
        addBtn.text = "Add";
    }

    function editStep(index, dur, temp) {
        addView.visible = true;
        addView.index = index;
        durationText.text = dur;
        temperatureText.text = temp;
        headline.text = "Edit mash step " + index;
        addBtn.text = "Edit";
    }

    function isTempValid() {
        return addView.temperature >= addView.minTemperature 
            && addView.temperature < addView.maxTemperature
    }
    function isDurValid() {
        return addView.duration >= addView.minDuration 
            && addView.duration < addView.maxDuration 
    }

    color: "black"
    height: 140

    Text {
        id: headline
        text: 'blub'
        font { pixelSize: 20; bold: true }
        color: 'white'
        anchors { top: parent.top; topMargin: 5 }
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Column {
        id: column
        spacing: 3
        anchors { top: headline.bottom; topMargin: 10; left: parent.left; leftMargin: 5; right: parent.right }

        Row {
            Text { color: "white"; text: "Temperature:"; width: 100 }
            TextField {
                id: temperatureText
                placeholderText: '[°C]'
                width: 50
            }
        }
        Row {
            Text { color: "white"; text: "Duration:"; width: 100 }
            TextField {
                id: durationText
                placeholderText: '[min]'
                width: 50
            }
        }
    }

    Button {
        id: cancelBtn
        text: 'Cancel'
        anchors { right: addBtn.left; bottom: parent.bottom; rightMargin: 5; bottomMargin: 5 }
        onClicked: addView.canceled()
    }

    Button {
        id: addBtn
        text: 'Add'
        width: cancelBtn.width
        anchors { right: parent.right; bottom: parent.bottom; rightMargin: 5; bottomMargin: 5 }
        onClicked: {
            if (!isDurValid() || !isTempValid()) 
               errorDialog.visible = true 
            else
                addView.accepted()
        }
    }


    //---------------------------------------------------------------------

    MessageDialog {
        id: errorDialog 
        title: !isDurValid() 
                ? "Invalid Duration" 
                : "Invalid Temperature"
        text: !isDurValid() 
                ? "Please enter a value for duration in the range " + minDuration + " - " + maxDuration
                : "Please enter a value for temperature in the range " + minTemperature + " - " + maxTemperature 
        visible: false
        onAccepted: visible = false
    }
}
