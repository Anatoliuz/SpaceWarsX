#ifndef RIB_H
#define RIB_H

#include <ribstruct.h>
#include "planet.h"
//#include
class rib{
public:
    rib();
    rib(planet &planetOne, planet &planetTwo, int numberOfPlayers);

    int getNumb1();   // Возвращает номер первой планеты
    int getNumb2();   // Возвращает номер второй планеты

    list<ribStruct>* getMassOfPlayersLists();   // Возвращает массив структур ribStruct всех игроков

private:
    int numberOne;   // Номер первой планеты
    int numberTwo;   // Номер второй планеты

    list<ribStruct> *massOfPlayersListsOfStructs;   // Массив структур ribStruct всех игроков

    int determineClosestSector(double diff_X, double diff_Y);   // Определение ближайшей зоны
    void determineSectorsOfConnection(int firstClosestSector, int &leftConnect, int &rightConnect);   // Пределение зоны вылетов
};

#endif // RIB_H
