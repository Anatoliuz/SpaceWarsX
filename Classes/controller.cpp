#include "controller.h"

controller::controller(int playerNumber)
{
    playerNum = playerNumber;
    planetId1 = -1; // -1, т.к все номера планет больше 0
    planetId2 = -1; // поэтому при -1 планета не выбрана
    action = 0;
}

void controller::reset()
{
    planetId1 = -1; // -1, т.к все номера планет больше 0
    planetId2 = -1; // поэтому при -1 планета не выбрана
    action = 0;
}

string controller::getAction()
{
    string result;
    if (action == 1 && planetId1 >= 0) {
        result = " createBuilding " +
                std::to_string(planetId1) +
                " " +
                std::to_string(playerNum) +
                " ||";
        reset(); // т.к действие обработано, надо его обнулить
        return result;
    }
    if (action == 2 && planetId1 != planetId2 && planetId1 >= 0 && planetId2 >= 0) {
        result = " move " +
                std::to_string(planetId1) +
                " " +
                std::to_string(planetId2) +
                " " +
                std::to_string(1) + // кол-во кораблей
                " " +
                std::to_string(playerNum) + // поменять 1 на playerInfo.playerNum
                " ||";
        reset(); // т.к действие обработано, надо его обнулить
        return result;
    }
    return "";
}

void controller::setCommand(int planetId1_, int planetId2_, int action_)
{
    planetId1 = planetId1_;
    planetId2 = planetId2_;
    action = action_;
}

void controller::setAction(int action_)
{
    setCommand(planetId1, planetId2, action_);
}

void controller::setPlanet1(int planetId)
{
    setCommand(planetId, planetId2, action);
}

void controller::setPlanet2(int planetId)
{
    setCommand(planetId1, planetId, action);
}


