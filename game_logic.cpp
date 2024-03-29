#include "game_logic.h"
#include <QDebug>
#include <QQuickWindow>

GameLogic::GameLogic(QMLBridge& bridge, QGuiApplication& app, QQmlApplicationEngine& engine)
    : m_qmlBridge(bridge)
    , m_guiApplication(app)
    , m_qmlApplicationEngine(engine)
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
    m_hallOfFame = std::make_unique<HallOfFame>(&app);
    m_timer = std::make_unique<MoveTimer>(this, &app);
}

void GameLogic::gridIndexChanged(const int index)
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
        else
        {
            m_timer->startTimer();
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

    if (m_counter == MAX_SLOTS)
    {
        handleVictory(DRAW);
    }
}

void GameLogic::makeComputersMove()
{
    qDebug() << "makeComputersMove()";

    const int slot = findFreeSlot();
    qDebug() << "makeComputersMove() found free slot: " << slot;

    if (slot != INVALID_SLOT)
    {
        m_qmlBridge.sendComputersMove(slot);
    }
}

int GameLogic::findFreeSlot()
{
    // Find free slot
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        bool found = false;
        if (std::find(m_playerOneMoves.begin(), m_playerOneMoves.end(), i) != m_playerOneMoves.end())
        {
            found = true;
        }

        if (std::find(m_playerTwoMoves.begin(), m_playerTwoMoves.end(), i) != m_playerTwoMoves.end())
        {
            found = true;
        }

        if (found == false)
        {
            return i;
        }
    }

    return -1;
}

void GameLogic::handleVictory(GameLogic::Player player)
{
    if (player == GameLogic::PLAYER_ONE)
    {
        qDebug() << "The winner is player one!";

        QString name = "Player One";
        QString message = m_hallOfFame->addEntry(name);

        m_qmlBridge.sendShowDialogSignal(message);
    }
    else if (player == GameLogic::PLAYER_TWO)
    {
        qDebug() << "The winner is player two!";

        QString name = "Player Two";
        QString message = m_hallOfFame->addEntry(name);

        m_qmlBridge.sendShowDialogSignal(message);
    }
    else {
        qDebug() << "No winner! Draw!";

        QString name = "No winner";
        QString message = m_hallOfFame->addEntry(name);

        m_qmlBridge.sendShowDialogSignal(message);
    }
}

GameLogic::Player GameLogic::getPlayer()
{
    const int modulo = m_counter % 2;

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

        for (const int value : combination) {

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

void GameLogic::exitGame()
{
    m_guiApplication.quit();
}

void GameLogic::playAgain()
{
    m_playerOneMoves.clear();
    m_playerTwoMoves.clear();
    m_counter = 0;
}

