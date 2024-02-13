#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "qml_bridge.h"
#include "qml_bridge_observer.h"
#include <vector>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "hall_of_fame.h"
#include "movetimer.h"

class GameLogic : public QmlBridgeObserver
{

public:

    const static int MAX_SLOTS = 9;
    const static int INVALID_SLOT = -1;

    enum Player {
        PLAYER_ONE,
        PLAYER_TWO,
        DRAW
    };

    GameLogic(QMLBridge& bridge, QGuiApplication& app, QQmlApplicationEngine& engine);

    void makeComputersMove();

    // From QmlBridgeObserver
    void gridIndexChanged(const int index);
    void exitGame();
    void playAgain();

private:
    GameLogic::Player getPlayer();
    bool isVictory(const std::vector<int>& moves, GameLogic::Player player);
    void handleVictory(GameLogic::Player player);
    int findFreeSlot();

private:
    QMLBridge& m_qmlBridge;
    QGuiApplication& m_guiApplication;
    QQmlApplicationEngine& m_qmlApplicationEngine;
    int m_counter;
    const std::vector<std::vector<int>> m_winningCombinations;
    std::vector<int> m_playerOneMoves;
    std::vector<int> m_playerTwoMoves;
    std::unique_ptr<HallOfFame> m_hallOfFame;
    std::unique_ptr<MoveTimer> m_timer;
};

#endif // GAME_LOGIC_H
