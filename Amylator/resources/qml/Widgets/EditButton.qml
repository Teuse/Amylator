import QtQuick 2.0

Item {
    id: button

    signal clicked

    //---------------------------------------------------------------------

    width:  17 
    height: 17 

    readonly property string imageNormal:   "../../images/buttons/edit_normal.png"
    readonly property string imagePressed:  "../../images/buttons/edit_pressed.png"
    readonly property string imageDisabled: "../../images/buttons/edit_pressed.png"

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
