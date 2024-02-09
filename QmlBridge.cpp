#include "QmlBridge.h"
#include <QDebug>
#include "QmlBridgeObserver.h"

QMLBridge::QMLBridge(QObject *parent) :
    QObject(parent)
{
}

QMLBridge::~QMLBridge()
{
    m_qmlBridgeObservers.clear();
}

void QMLBridge::setGridIndex(const int index)
{
    qDebug() << "Backend received index: " << index;
    notifyGridIndexChanged(index);
}

void QMLBridge::exitGame()
{
    notifyExitGame();
}

void QMLBridge::playAgain()
{
    notifyPlayAgain();
}

void QMLBridge::sendShowDialogSignal(const QString& message)
{
    emit showDialog(message);
}

void QMLBridge::registerObserver(QmlBridgeObserver* observer)
{
    m_qmlBridgeObservers.push_back(observer);
}

void QMLBridge::notifyGridIndexChanged(int index)
{
    for (QmlBridgeObserver* observer : m_qmlBridgeObservers)
    {
        observer->gridIndexChanged(index);
    }
}

void QMLBridge::notifyExitGame()
{
    for (QmlBridgeObserver* observer : m_qmlBridgeObservers)
    {
        observer->exitGame();
    }
}

void QMLBridge::notifyPlayAgain()
{
    for (QmlBridgeObserver* observer : m_qmlBridgeObservers)
    {
        observer->playAgain();
    }
}

