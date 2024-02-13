#ifndef MOVETIMER_H
#define MOVETIMER_H

#include <QObject>
#include <QTimer>

class GameLogic;

class MoveTimer : public QObject
{
    Q_OBJECT
public:
    explicit MoveTimer(GameLogic* m_logic, QObject *parent = nullptr);

    void startTimer();

private:
    void onTimer();


private:
    QTimer* m_timer;
    GameLogic* m_logic;

signals:
};

#endif // MOVETIMER_H
