import QtQuick 2.12
import QtQuick.Window 2.12
import TopWordsModel 1.0
import QtQuick.Dialogs 1.0

Window {
    id: mainWindow
    visible: false
    width: 800
    height: 600
    title: qsTr("Word histo...")
    property int elementWidth: (width - 10*(15+1)) / 15
    property int percOfWork: 0
    property TopWordsModel topWordsModel: TopWordsModel {
        onPercentDone: {
            percOfWork = percent
            textFileProgress.text = qsTr("Processing file ") + percOfWork + qsTr("%")
        }
        onWorkFinished: {
            percOfWork = 100
            textFileProgress.text = qsTr("Work done")
       }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file to calculate top words"
        folder: shortcuts.home
        selectFolder: false
        onAccepted: {
            mainWindow.visible = true;
            topWordsModel.startWithFilePath(fileDialog.fileUrl.toString().replace('file://',''));
        }
        onRejected: {
            Qt.quit()
        }
        Component.onCompleted: visible = true
    }

    Rectangle {
        id: fileProgressBack
        color: "grey"
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            id: fileProgress
            color: "white"
            anchors.fill: parent
            anchors.margins: 5

            Rectangle {
                id: fileProgressPercent
                color: "#d2edff"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: parent.width * percOfWork / 100
            }

            Text {
              id: textFileProgress
              color: "black"
              text: qsTr("File progress at:")
              font.pixelSize: 20
              anchors.bottom: parent.bottom
              anchors.left: parent.left
              anchors.right: parent.right
              anchors.bottomMargin: 10
            }
        }
    }

    ListView {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: fileProgressBack.top
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        spacing: 10
        model: topWordsModel
        orientation: ListView.Horizontal
        delegate: BarChartColumn {
            colColor: "#00FF00"
            colText: model.word
            anchors.bottom: parent.bottom
            height: parent.height * model.percent
            width: elementWidth
        }
    }
}
