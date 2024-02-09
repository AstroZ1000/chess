#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "QmlBridge.h"
#include "QmlBridgeObserver.h"
#include <vector>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class GameLogic : public QmlBridgeObserver
{
public:

    enum Player {
        PLAYER_ONE,
        PLAYER_TWO
    };

    GameLogic(QMLBridge& backEnd, QGuiApplication& app, QQmlApplicationEngine& engine);

    // From QmlBridgeObserver
    void gridIndexChanged(const int index);
    void exitGame();
    void playAgain();

private:
    GameLogic::Player getPlayer();
    bool isVictory(const std::vector<int>& moves, GameLogic::Player player);
    void handleVictory(GameLogic::Player player);

private:
    QMLBridge& m_qmlBridge;
    QGuiApplication& m_guiApplication;
    QQmlApplicationEngine& m_qmlApplicationEngine;
    int m_counter;
    const std::vector<std::vector<int>> m_winningCombinations;
    std::vector<int> m_playerOneMoves;
    std::vector<int> m_playerTwoMoves;
};

#endif // GAMELOGIC_H
