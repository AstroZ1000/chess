#include "GameLogic.h"
#include <QDebug>

GameLogic::GameLogic(QMLBridge& bridge)
    : m_qmlBridge(bridge)
    , m_counter(0)

    // Grid indexes
    //
    // 0 1 2
    // 3 4 5
    // 6 7 8
    , m_winningCombinations ({
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}})
{
    m_qmlBridge.registerObserver(this);
}

// TODO: make destructor and remove observer

void GameLogic::gridIndexUpdated(int index)
{
    m_counter++;
    GameLogic::Player player = getPlayer();

    switch (player)
    {
    case PLAYER_ONE:
    {
        m_playerOneMoves.push_back(index);
        if (isVictory(m_playerOneMoves, player))
        {
            handleVictory(PLAYER_ONE);
        }
        break;
    }

    case PLAYER_TWO:
    {
        m_playerTwoMoves.push_back(index);
        if (isVictory(m_playerTwoMoves, player))
        {
            handleVictory(PLAYER_TWO);
        }
        break;
    }

    default:
        break;
    }
}

void GameLogic::handleVictory(GameLogic::Player player)
{
    if (player == GameLogic::PLAYER_ONE)
    {
        qDebug() << "The winner is player one!";
        m_qmlBridge.sendShowDialogSignal("Congratulations player CROSSES!!!\n Want to try again?");
    }
    else
    {
        qDebug() << "The winner is player two!";
        m_qmlBridge.sendShowDialogSignal("Congratulations player NOUGHTS!!!\n Want to try again?");
    }
}

GameLogic::Player GameLogic::getPlayer()
{
    int modulo = m_counter % 2;

    if (modulo == 1)
    {
        return GameLogic::PLAYER_ONE;
    }
    else
    {
        return GameLogic::PLAYER_TWO;
    }
}

bool GameLogic::isVictory(const std::vector<int>& moves, GameLogic::Player player)
{
    qDebug() << "========isVictory========";
    qDebug() << "player is: " << player << "moves are: " << moves;

    for (const auto& combination : m_winningCombinations) {

        qDebug() << "winning combination: " << combination;
        bool victory = true;

        for (int value : combination) {

            qDebug() << "value: " << value;

            if (std::find(moves.begin(), moves.end(), value) == moves.end()) {
                victory = false;
                break;
            }
        }

        if (victory)
        {
            return true;
        }
    }

    return false;
}
