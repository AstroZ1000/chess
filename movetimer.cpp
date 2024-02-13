#include "movetimer.h"
#include <QDebug>
#include "game_logic.h"

MoveTimer::MoveTimer(GameLogic* logic, QObject *parent)
    : QObject{parent}
    , m_logic(logic)
{
    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, this, &MoveTimer::onTimer);
    m_timer->setSingleShot(true);

}

void MoveTimer::onTimer()
{
    qDebug() << "onTimer()";
    m_logic->makeComputersMove();
}

void MoveTimer::startTimer()
{
    m_timer->start(1000);
}
