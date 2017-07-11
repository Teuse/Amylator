import QtQuick 2.0

Item {
    id: button 

    signal cicked

    //---------------------------------------------------------------------
    
    width: 11; height: 13

    Rectangle { 
        anchors.left: parent.left  
        color: header.running ? "#049716" : "white"
        height: parent.height 
        width: 4 
    }
    Rectangle { 
        anchors.right:parent.right 
        color: header.running ? "#049716" : "white" 
        height: parent.height 
        width: 4 
    }
    MouseArea { 
        anchors.fill: parent 
        onClicked: button.clicked()
    }
}


