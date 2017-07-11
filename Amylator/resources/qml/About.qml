import QtQuick 2.0


Item {
    id: aboutView 

    property string version: "0.0.0"
    
    visible: false

    MouseArea {
        anchors.fill: parent
        onClicked: aboutView.visible = false
    }

    Rectangle {
        id: background
        color: "black"
        opacity: 0.7
        anchors.fill: parent
    }

    Rectangle {
        width: 400
        height: 300
        color: "orange"
        anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter } 

        Text { 
            text: "Brew Control" 
            color: "black"
            anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter } 
            font    { pixelSize: 33; bold: true }
        }

        Text {
            text: version
            color: "black"
            anchors { left: parent.left; top: parent.top; leftMargin: 5; topMargin: 5 }
            font    { pixelSize: 18; bold: true }
        }

    }
}
