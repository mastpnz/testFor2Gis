import QtQuick 2.0

Item {
    property string colText: "word"
    property color colColor: "green"
    property color textColor: "black"

    Rectangle {
        color: colColor
        width: parent.width
        height: parent.height

        Text {
          id: text1
          color: textColor
          text: qsTr(colText)
          font.pixelSize: 20
          anchors.bottom: parent.bottom
          anchors.left: parent.left
          anchors.right: parent.right
          anchors.bottomMargin: 20
          rotation: -90
        }
    }
}
