import QtQuick 2.0


Rectangle {
    id: networkView

    property var network

    color: "black"
    visible: false

    Text { 
        text:  network.connected ? "Connected to Server" : "Can't connect to server..."
        color: "white"
        anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter } 
        font    { pixelSize: 33; bold: true }
    }
}
