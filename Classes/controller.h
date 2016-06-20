#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#define CREATE_BUILDING 1
#define MOVE 2
#define WIN 3

using std::string;

class controller
{
 public:
    controller(int playerNumber);
/*
    void setCommand (int planetId1 = -1, int planetId2_ = -1, int action = 0);
    void setPlanet1 (int planetId);
    void setPlanet2 (int planetId);
    void setAction  (int action);
*/
    void setMove (int planetId1, int planetId2, int numberOfUnits);
    void setCreateBuilding(int planetId);
    void setWin();
    void reset(); // сброс параметров


    string getAction();
    int playerNum;

 private:
    int planetId1;
    int planetId2;
    int action; // 1 - постройка, 2 - перелет, 3 - сообщение на сервер о победе
    int numberOfUnits;
 // playerInfo* playerInf; // информация об игроке, нужен номер игрока
};
/* команды
   1 - постройка, задаешь planetId1 >= 0 и action = 1;
   2 - перелет, задаешь planteId1, planetId2, и action = 2;
   3 - сообщение о победе, просто вызываешь my_controller.setWin();
*/

#endif // CONTROLLER_H
