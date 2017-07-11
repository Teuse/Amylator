import QtQuick 2.0


Canvas {
    id: button 

    property bool highlighted: false 
    property bool stroke: true

    signal clicked

    //---------------------------------------------------------------------
    
    // antialiasing: true
    width: 13 
    height: 13

    onHighlightedChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d");
        ctx.save();
        ctx.clearRect(0, 0, button.width, button.height);
        ctx.fillStyle = button.highlighted ? "green" : "white"
        ctx.beginPath();

        ctx.moveTo(0,0);
        ctx.lineTo(0, button.height);
        ctx.lineTo(button.width, button.height/2);

        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }

    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
