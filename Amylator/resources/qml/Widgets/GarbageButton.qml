import QtQuick 2.0

Item {
    id: button

    signal clicked

    //---------------------------------------------------------------------

    width: 12
    height: 15 

    readonly property string imageNormal:   "../../images/buttons/garbage_normal.png"
    readonly property string imagePressed:  "../../images/buttons/garbage_pressed.png"
    readonly property string imageDisabled: "../../images/buttons/garbage_pressed.png"

    //---------------------------------------------------------------------

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: button.enabled ? imageNormal : imageDisabled 
    }

    MouseArea {
        anchors.fill: button
        onClicked:  button.clicked();
        onPressed:  backgroundImage.source = imagePressed 
        onReleased: backgroundImage.source = (button.enabled ? imageNormal : imageDisabled)
    }
}
