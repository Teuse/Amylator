import QtQuick 2.0

Item {
    id: root 

    signal leftClicked
    signal rightClicked
    signal zoomInClicked
    signal zoomOutClicked

    //---------------------------------------------------------------------

    width: 60 
    height: 60 

    //---------------------------------------------------------------------

    Rectangle {
        id: background
        anchors.fill: parent
        radius: width * 0.5
        color: "white"
        opacity: 0.4
    }

    ZoomPadButton {
        id: upButton
        symbol: "+"
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 4 }
        onClicked: zoomInClicked()
    }

    ZoomPadButton {
        id: downButton
        symbol: "-"
        anchors { horizontalCenter: parent.horizontalCenter; bottom: parent.bottom; bottomMargin: 4 }
        onClicked: zoomOutClicked()
    }

    ZoomPadButton {
        id: leftButton
        symbol: "-"
        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 4 }
        onClicked: leftClicked()
    }

    ZoomPadButton {
        id: rightButton
        symbol: "+"
        anchors { verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: 4 }
        onClicked: rightClicked()
    }
}
