#include "gamestate.h"

GameState::GameState()
{
    blacklPoints = 0;
    whitePoints = 0;
    ifHereWhite = true;
}

int GameState::getBlackPoints()
{
    return blacklPoints;
}

int GameState::getWhitePoints()
{
    return whitePoints;
}

bool GameState::getIfHereWhite()
{
    return ifHereWhite;
}

void GameState::setWhitePoints(int points)
{
    this->whitePoints = points;
}

void GameState::setBlackPoints(int points)
{
    this->blacklPoints = points;
}

void GameState::setIfHereWhite(bool var)
{
    this->ifHereWhite = var;
}
