#include "datamodel.h"


dataModel::dataModel(int numberOfPlayers_, int playerId_)
{
    numberOfPlayers = numberOfPlayers_;
    playerId = playerId_;
    winnerId = -1; // нет победителя
}
