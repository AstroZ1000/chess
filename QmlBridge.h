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
    ~QMLBridge();

    void registerObserver(QmlBridgeObserver* observer);
    void sendShowDialogSignal(const QString& message);

signals:
    void showDialog(const QString& message);

public slots:
    void setGridIndex(const int index);
    void exitGame();
    void playAgain();

private:
    void notifyGridIndexChanged(int index);
    void notifyExitGame();
    void notifyPlayAgain();

private:
    std::vector<QmlBridgeObserver*> m_qmlBridgeObservers;
};

#endif // QMLBRIDGE_H
