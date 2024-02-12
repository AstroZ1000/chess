import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 600
    height: 600
    visible: true
    title: qsTr("Antti's Noughts and Crosses")

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
                id: repeater
                model: 9

                Rectangle {
                    width: gridLayout.width / 3
                    height: gridLayout.height / 3
                    color: "lightblue"

                    Image {
                        id: cross
                        source: "file:////home/astroz/projects/Chess/images/cross.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        visible: false
                    }

                    Image {
                        id: nought
                        source: "file:////home/astroz/projects/Chess/images/nought.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        visible: false
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {

                            counter++

                            let modulo = counter % 2
                            if (modulo == 1) {
                                cross.visible = true;
                            } else {
                                nought.visible = true;
                            }

                            console.log("Rectangle clicked: index = " + index + " + counter = " + counter);
                            QMLBridge.setGridIndex(index);
                        }
                    }

                    Connections {
                        target: yesButton
                        function onRefreshUi() {

                            cross.visible = false;
                            nought.visible = false;
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: gameOverDialog
        title: "Game Over"
        anchors.centerIn: parent

        Row {
            spacing: 30
            Button {

                signal refreshUi()

                id: yesButton
                text: "Yes SIR!"

                onClicked: {
                    gameOverDialog.close()
                    counter = 0
                    refreshUi()
                    QMLBridge.playAgain()
                }
            }

            Button {
                text: "No way!"
                onClicked: {
                    gameOverDialog.close()
                    QMLBridge.exitGame()
                }
            }
        }
    }

    Connections {
        target: QMLBridge

        function onShowDialog(message) {
            gameOverDialog.title = message
            gameOverDialog.open()
        }
    }
}
