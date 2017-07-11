import QtQuick 2.0
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "../Widgets" as Widgets 


Item {
    id: header 

    signal plusClicked
    signal clearClicked

    //---------------------------------------------------------------------

    height: headerBar.height
    
    //---------------------------------------------------------------------
    
    Widgets.HeaderBar {
        id: headerBar
        width: header.width
        text: "Schedule"
    }

    //---------------------------------------------------------------------
    
    Widgets.GarbageButton {
        id: clearBtn
        anchors { right: parent.right; rightMargin: 10 }
        anchors.verticalCenter: parent.verticalCenter
        onClicked: header.clearClicked()
    }

    Widgets.PlusButton {
        id: plusBtn
        anchors { right: clearBtn.left; rightMargin: 10 }
        anchors.verticalCenter: parent.verticalCenter
        onClicked: header.plusClicked()
    }

}
