#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

using std::string;

class controller
{
 public:
    controller(int playerNumber);
    int planetId1;
    int planetId2;
    int action; // 1 - постройка, 2 - перелет
    void reset(); // сброс параметров

    void setCommand (int planetId1 = -1, int planetId2_ = -1, int action = 0);
    void setPlanet1 (int planetId);
    void setPlanet2 (int planetId);
    void setAction  (int action);


    string getAction();
    int playerNum;
 // playerInfo* playerInf; // информация об игроке, нужен номер игрока
};
/*
cont -> setCommand(1, 2, 2);
равносильно
cont -> setAction(2);
cont -> setPlanet1(1);
cont -> setPlanet2(2);
*/

#endif // CONTROLLER_H
