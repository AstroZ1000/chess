#ifndef QML_BRIDGE_OBSERVER_H
#define QML_BRIDGE_OBSERVER_H

class QmlBridgeObserver {
public:
    virtual void gridIndexChanged(const int index) = 0;
    virtual void exitGame() = 0;
    virtual void playAgain() = 0;
};

#endif // QML_BRIDGE_OBSERVER_H
