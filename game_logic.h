#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "QmlBridge.h"
#include "QmlBridgeObserver.h"
#include <vector>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "hall_of_fame.h"

class GameLogic : public QmlBridgeObserver
{

public:

    enum Player {
        PLAYER_ONE,
        PLAYER_TWO
    };

    GameLogic(QMLBridge& bridge, QGuiApplication& app, QQmlApplicationEngine& engine);

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
    std::unique_ptr<HallOfFame> m_hallOfFame;
};

#endif // GAME_LOGIC_H
