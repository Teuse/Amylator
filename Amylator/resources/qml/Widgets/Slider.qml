import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0


Item {
  id: slider

  property alias handleStyle: handle.sourceComponent
  property alias grooveStyle: grooveLoader.sourceComponent
  property alias currentPixelPos: handle.x
  property var    range:            [0.0, 1.0]
  property string unit:             ""

  property real   distance:         Math.abs(range[1] - range[0])
  property real   defaultValue
  property real   value:            0
  property string displayValue:     formattedDisplayValue()
  property int    fractionalDigits: 1

  property bool   mouseAction:      mouseHandle.containsMouse || mouseSlider.pressed

  signal mouseX()
  Component.onCompleted: { mouseSlider.mouseXChanged.connect(mouseX); reset(); }

  property real   coarseStep:       1.0
  property real   fineStep:         coarseStep / 10
  property real   currentStep:      mouseSlider.shift ? fineStep : coarseStep

  implicitHeight: 12

  onDefaultValueChanged: { reset(); }

  onValueChanged: {
    var newHandleX = valueToHandlePos(value)
    if ( handle.x !== newHandleX )
      handle.x = newHandleX
  }

  onWidthChanged:  {
    var newHandleX = valueToHandlePos(value)
    if ( handle.x !== newHandleX ) {
      handle.x = newHandleX
      value = handlePosToValue(handle.x)
    }
  }

  function reset() {
    if (defaultValue !== undefined) value = defaultValue;
  }

  function valueToHandlePos(value) {
    return distance === 0 ? 0 : (value - range[0]) * width/distance - handle.width/2
  }

  function handlePosToValue(handle_pos) {
    var delta_pos = (mouseSlider.x_pos - handle_pos) * currentStep
    var val       = ((mouseSlider.x_pos - delta_pos) + handle.width/2) * distance/width  + range[0]
    return width === 0 ? 0 : clamp(val, range[0], range[1])
  }

  function formattedDisplayValue() {
    var sign = value < 0 ? "- " : ""
    return sign + Math.abs(value).toFixed(fractionalDigits) + " " + unit
  }


  function clamp( valVal, minVal, maxVal ) {
    return Math.max(Math.min(valVal, maxVal), minVal)
  }

  function isXOnHandle(x) {
    var low  = handle.x + handle.width/2;
    var high = low + handle.width;
    return (x > low  &&  x < high);
  }


  Loader {
    id: grooveLoader
    sourceComponent: defaultGroove
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    width : grooveLoader.item.width
    height: grooveLoader.item.height
  }

  Loader {
    id: handle
    anchors.verticalCenter: parent.verticalCenter
    x: valueToHandlePos(value)
    width : item.width
    height: item.height
    sourceComponent: defaultHandle
  }

  MouseArea {
    id: mouseHandle
    hoverEnabled: true
    anchors.centerIn: handle
    anchors.fill: handle
  }



  MouseArea {
    id: mouseSlider
    anchors.centerIn: parent
    height: parent.height
    width:  parent.width + handle.width

    property real x_pos: 0
    property bool shift: false
    property int  clickCounter:       0
    property bool firstClickOnHandle: false
    property bool resetTriggered:     false

    function currentXPos() { return x + (mouseX - handle.width/2) }

    onShiftChanged: x_pos = currentXPos()

    onMouseXChanged: {
      if ( ! resetTriggered ) {
        shift = mouse.modifiers & Qt.ShiftModifier
        slider.value = handlePosToValue(currentXPos())
      }
    }

    Timer {
      id: doubleClickTimer
      interval: 300; repeat: false
      onTriggered: mouseSlider.clickCounter = 0;
    }

    /* We can not use "onDoubleClicked" here, because we need to check, if the first click
    occured on the handle or not. Only if the first click was on the handle, we trigger
    reset. The problem with onDoulbeClick is, that we will always receive a onPressed
    before and therefore, we can not say, if the click was on the handle or not.  */
    onPressed:
    {
      x_pos        = currentXPos();
      clickCounter = clickCounter + 1;

      if (clickCounter == 2 && firstClickOnHandle)
      {
        slider.reset();
        firstClickOnHandle = false;
        resetTriggered     = true;
      }
      else
      {
        doubleClickTimer.restart();
        firstClickOnHandle = isXOnHandle(mouseX);
        resetTriggered     = false;
      }
    }
  }

  Component {
    id: defaultHandle
    Item {
      width : 12
      height: 12
      y: parent.y - 2
      Image {
        id: img
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "../../images/fader_handle.svg"
        visible: false
        opacity: 1
      }
      ColorOverlay { anchors.fill: parent; source: img; color: Color.sliderHandleColor }
    }
  }

  Component {
    id: defaultGroove
    Rectangle {
      width: slider.width + 1
      height: 1
      color: Color.sliderGrooveColor
    }
  }
}
