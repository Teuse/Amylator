import QtQuick 2.0
import QtCharts 2.1
import './Widgets' as Widget


ChartView {
    id: chartView

    property var dataSource

    //---------------------------------------------------------------------

    animationOptions: ChartView.NoAnimation
    theme:            ChartView.ChartThemeDark

    Component.onCompleted: dataSource.setSeries(lineSeries1)

    //---------------------------------------------------------------------

    ValueAxis { id: yAxis; min: 0; max: 100 }
    // ValueAxis { id: xAxis; min: 0; max: 60; tickCount: 7; minorTickCount: 0 }
    ValueAxis { id: xAxis; min: 0; max: 8; tickCount: 5; minorTickCount: 0 }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        useOpenGL: true 
        axisX: xAxis 
        axisY: yAxis 
    }

    //---------------------------------------------------------------------

    Widget.ZoomPad {
        id: zoomPad
        anchors { right: parent.right; top: parent.top; rightMargin: 15; topMargin: 15 }
    }
}
