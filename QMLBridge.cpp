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

void QMLBridge::sendSignal()
{
    emit showDialog();
}

void QMLBridge::registerObserver(QmlBridgeObserver* observer)
{
    m_QMLBridgeObservers.push_back(observer);
}

void QMLBridge::notifyObservers(int index)
{
    for (QmlBridgeObserver* observer : m_QMLBridgeObservers)
    {
        observer->gridIndexUpdated(index);
    }
}
