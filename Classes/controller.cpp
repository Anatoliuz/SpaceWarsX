#include "controller.h"

// функции создания строк-команд
//======
string commandCreateBuilding (const int& planetId, const int& playerNumber)
{
    string result = " createBuilding " +
                std::to_string(planetId) + // где строится
                " " +
                std::to_string(playerNumber) + // номер строителя
                " ||";
    return result;
}

string commandMove (const int& planetId1, const int& planetId2, const int& numberOfUnits, const int& playerNumber)
{
    string result = " move " +
        std::to_string(planetId1) + //откуда
        " " +
        std::to_string(planetId2) + //куда
        " " +
        std::to_string(numberOfUnits) + // кол-во кораблей
        " " +
        std::to_string(playerNumber) +  // номер игрока чьи корабли
        " ||";
    return result;
}

string commandWin (const int& playerNumber)
{
    string result = "|| WIN " + std::to_string(playerNumber) + " ||";
    return result;
}
//======

controller::controller(int playerNumber)
{
    playerNum = playerNumber;
    planetId1 = -1; // -1, т.к все номера планет больше 0
    planetId2 = -1; // поэтому при -1 планета не выбрана
    numberOfUnits = 0; 
    action = 0;
}

void controller::reset()
{
    planetId1 = -1; // -1, т.к все номера планет больше 0
    planetId2 = -1; // поэтому при -1 планета не выбрана
    action = 0; // нет действия
}

string controller::getAction()
{
    string result;

    switch (action){
        case CREATE_BUILDING:
            if (planetId1 >= 0) {
                result = commandCreateBuilding(planetId1, playerNum);
                reset(); // т.к действие обработано, надо его обнулить
              //  return result;
            }
            break;
        case MOVE:
            if (planetId1 != planetId2 && planetId1 >= 0 && planetId2 >= 0) {
                result = commandMove(planetId1, planetId2, numberOfUnits, playerNum);
                reset();
            }
            break;
        case WIN:
            result = commandWin(playerNum);
            reset();
            break;
    }
    return result;
}

void controller::setMove(int planetId1_, int planetId2_, int numberOfUnits_)
{
    planetId1 = planetId1_;
    planetId2 = planetId2_;
    numberOfUnits = numberOfUnits_;
    action = MOVE;
}

void controller::setCreateBuilding(int planetId1_)
{
    planetId1 = planetId1_;
    action = CREATE_BUILDING;
}

void controller::setWin()
{
    action = WIN;
}

/*

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
}*/


