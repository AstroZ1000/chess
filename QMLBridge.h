#ifndef QMLBRIDGE_H
#define QMLBRIDGE_H

#include <QObject>
#include <qqml.h>
#include <vector>

class QmlBridgeObserver;

class QMLBridge : public QObject
{
    Q_OBJECT

public:
    explicit QMLBridge(QObject *parent = nullptr);

    void registerObserver(QmlBridgeObserver* observer);
    void sendSignal();

signals:
    void showDialog();

public slots:
    void setGridIndex(const int index);

private:
    void notifyObservers(int index);

private:
    std::vector<QmlBridgeObserver*> m_QMLBridgeObservers;
};

#endif // QMLBRIDGE_H
