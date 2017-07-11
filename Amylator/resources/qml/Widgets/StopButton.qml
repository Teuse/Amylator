import QtQuick 2.0

Rectangle {
    id: button 

    signal clicked

    //---------------------------------------------------------------------
    
    width: 13 
    height: 13
    color: "white"

    MouseArea { 
        anchors.fill: parent 
        onClicked: button.clicked() 
    }
}

