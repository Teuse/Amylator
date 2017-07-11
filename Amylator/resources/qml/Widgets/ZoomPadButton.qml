import QtQuick 2.0


Rectangle {
    id: button 

    property string symbol: "+"
    signal clicked

    //---------------------------------------------------------------------

    width: 15
    height: 15
    color: "transparent"
    border { color: "black"; width: 1 }

    Text { 
        text: button.symbol 
        anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter }
    }

    MouseArea {
        anchors.fill: button
        onClicked:  button.clicked();
        onPressed:  button.color = "white" 
        onReleased: button.color = "transparent" 
    }
}

