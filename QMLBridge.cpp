#include "QMLBridge.h"
#include <QDebug>
#include "QMLBridgeObserver.h"

QMLBridge::QMLBridge(QObject *parent) :
    QObject(parent)
{
}

void QMLBridge::setGridIndex(const int index)
{
    qDebug() << "Backend received index: " << index;
    notifyObservers(index);
}

void QMLBridge::sendShowDialogSignal(const QString& message)
{
    emit showDialog(message);
}

void QMLBridge::registerObserver(QmlBridgeObserver* observer)
{
    m_qmlBridgeObservers.push_back(observer);
}

void QMLBridge::notifyObservers(int index)
{
    for (QmlBridgeObserver* observer : m_qmlBridgeObservers)
    {
        observer->gridIndexUpdated(index);
    }
}
