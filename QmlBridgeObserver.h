#ifndef QMLBRIDGEOBSERVER_H
#define QMLBRIDGEOBSERVER_H

class QmlBridgeObserver {
public:
    virtual void gridIndexChanged(int index) = 0;
    virtual void exitGame() = 0;
    virtual void playAgain() = 0;
};

#endif // QMLBRIDGEOBSERVER_H
