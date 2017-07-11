pragma Singleton
import QtQuick 2.0

QtObject {

  function rgba(r,g,b,a){
    return Qt.rgba(r/255. , g/255. , b/255. , a)
  }

  readonly property color orange:           rgba (255 , 150 ,   0 , 1.0)
  readonly property color orangeDark:       rgba (204 , 120 ,   0 , 1.0)

  readonly property color green:            rgba ( 25 , 255 ,  97 , 1.0)

  readonly property color headerGrayBright: rgba ( 34 ,  36 ,  44 , 1.0)
  readonly property color headerGrayDark:   rgba ( 28 ,  28 ,  36 , 1.0)
}
