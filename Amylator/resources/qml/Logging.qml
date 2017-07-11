import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import BrewComponent 1.0 as BC
import './Definitions'
import "./Widgets" as Widgets 


Item {
    id: root 

    BC.Logging { id: logging }
    
    //---------------------------------------------------------------------

    Widgets.HeaderBar {
        id: headerBar
        width: root.width
        text: "Logging"
    }

    Widgets.GarbageButton {
        id: clearBtn
        anchors { right: parent.right; rightMargin: 10 }
        anchors.verticalCenter: parent.verticalCenter
        onClicked: logging.clear()
    }

    //---------------------------------------------------------------------
    
    TextArea {
        id: textField
        readOnly: true
        text: logging.text
        anchors { top: headerBar.bottom; bottom: parent.bottom; left: parent.left; right: parent.right }

        style: TextAreaStyle {
            textColor: "black"
            backgroundColor: Color.orange 
        }
    }

}
