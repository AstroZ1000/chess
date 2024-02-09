#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "QMLBridge.h"
#include "QMLBridgeObserver.h"
#include <vector>

class GameLogic : public QmlBridgeObserver
{
public:

    enum Player {
        PLAYER_ONE,
        PLAYER_TWO
    };

    GameLogic(QMLBridge& backEnd);

    // From BackEndObserver
    void gridIndexUpdated(int index);

private:
    GameLogic::Player getPlayer();
    bool isVictory(const std::vector<int>& moves, GameLogic::Player player);
    void handleVictory(GameLogic::Player player);

private:
    QMLBridge& m_backEnd;
    int m_counter;
    const std::vector<std::vector<int>> m_winningCombinations;
    std::vector<int> m_playerOneMoves;
    std::vector<int> m_playerTwoMoves;
};

#endif // GAMELOGIC_H
