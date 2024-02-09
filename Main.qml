import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 600
    height: 600
    visible: true
    title: qsTr("Antti's Chess")

    property int counter: 0

    Rectangle {
        anchors.fill: parent
        width: 600
        height: 600
        color: "black"

        GridLayout {
            id: gridLayout
            columns: 3
            rows: 3
            anchors.fill: parent
            columnSpacing: 5
            rowSpacing: 5

            Repeater {
                model: 9
                Rectangle {
                    width: gridLayout.width / 3
                    height: gridLayout.height / 3
                    color: "lightblue"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            counter++
                            console.log("Rectangle clicked: index = " + index + " + counter = " + counter);
                            BackEnd.setGridIndex(index);
                        }
                    }                                        
                }
            }
        }
    }

    Dialog {
        id: gameOverDialog
        title: "Game Over"

        Row {
            spacing: 30
            Button {
                text: "Ok"
                onClicked: gameOverDialog.close()
            }
        }
    }

    Connections {
        target: BackEnd

        onShowDialog: {
            gameOverDialog.open()
        }
    }
}
