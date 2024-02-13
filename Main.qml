import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 600
    height: 600
    visible: true
    title: qsTr("Antti's Noughts and Crosses")

    property int counter: 0
    property var usedIndexes: []

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
                        id: background
                        source: "images/artboard_" + index + ".png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        visible: true
                    }

                    Image {
                        id: cross
                        source: "images/blue.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        visible: false
                    }

                    Image {
                        id: nought
                        source: "images/red.png"
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        visible: false
                    }

                    function isAllowedIndex(value) {
                        for (var i = 0; i < usedIndexes.length; i++) {
                            if (usedIndexes[i] === value) {
                                return false;
                            }
                        }

                        return true;
                    }

                    function makeMove(value) {
                        if (isAllowedIndex(value)) {

                            usedIndexes.push(value);
                            counter++;

                            let modulo = counter % 2
                            if (modulo == 1) {
                                background.visible = false;
                                crossAnimation.start();
                                crossSizeAnimation.start();
                            } else {
                                background.visible = false;
                                noughtAnimation.start();
                                noughtSizeAnimation.start();
                            }

                            console.log("Rectangle clicked: index = " + value + " + counter = " + counter);
                            QMLBridge.setGridIndex(value);

                        } else {
                            console.log("Not allowed index = " + value);
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            makeMove(index);
                        }
                    }

                    SequentialAnimation {
                        id: crossAnimation

                        NumberAnimation {
                            target: cross
                            property: "opacity"
                            duration: 250
                            from: 1
                            to: 0
                        }
                        ScriptAction {
                            script: {
                                cross.visible = true;
                            }
                        }
                        NumberAnimation {
                            target: cross
                            property: "opacity"
                            from: 0
                            to: 1
                            duration: 250
                        }
                    }

                    SequentialAnimation {
                        id: crossSizeAnimation

                        NumberAnimation {
                            target: cross
                            property: "scale"
                            from: 1
                            to: 1.5
                            duration: 250
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: cross
                            property: "scale"
                            from: 1.5
                            to: 1
                            duration: 250
                            easing.type: Easing.InOutQuad
                        }
                    }

                    SequentialAnimation {
                        id: noughtAnimation

                        NumberAnimation {
                            target: nought
                            property: "opacity"
                            duration: 250
                            from: 1
                            to: 0
                        }
                        ScriptAction {
                            script: {
                                nought.visible = true;
                            }
                        }
                        NumberAnimation {
                            target: nought
                            property: "opacity"
                            from: 0
                            to: 1
                            duration: 250
                        }
                    }

                    SequentialAnimation {
                        id: noughtSizeAnimation

                        NumberAnimation {
                            target: nought
                            property: "scale"
                            from: 1
                            to: 1.5
                            duration: 250
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: nought
                            property: "scale"
                            from: 1.5
                            to: 1
                            duration: 250
                            easing.type: Easing.InOutQuad
                        }
                    }

                    Connections {
                        target: yesButton
                        function onRefreshUi() {

                            cross.visible = false;
                            nought.visible = false;
                            background.visible = true;
                        }
                    }

                    Connections {
                        target: QMLBridge

                        function onComputersMove(move) {
                            if (move === index) {
                                makeMove(index);
                                console.log("Computer moved to index = " + move);
                            }
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
                    usedIndexes = []
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
