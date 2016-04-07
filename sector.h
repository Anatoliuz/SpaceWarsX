#ifndef SECTOR_H
#define SECTOR_H

#include <list>
#include "Rocket.h"

using namespace std;

class sector{
public:
    sector();
    sector(double coord_X, double coord_Y, double diff_X, double diff_Y);

    // Наряду с конструктором сектора, используется для создания всех секторов в конструкторе планеты
    // (Скорее всего конструктор планеты будет немного переписан и этот метод будет убран)
    void changeCoordinates(double start_X, double start_Y, double finish_X, double finish_Y);

    void createUnit1();   // Создаёт юнит первого игрока в start сектора
    void createUnit2();   // Создаёт юнит второго игрока в finish сектора

    double getDifference_X();
    double getDifference_Y();
    list<Rocket>& getListOfUnits1();
    list<Rocket>& getListOfUnits2();

private:
    coordinate_X_Y start;    // Координаты начала сектора
    coordinate_X_Y finish;   // Координаты конца сектора

    double differecne_X;   // Разница между коодинатой X начала и конца
    double differecne_Y;   // Разница между коодинатой Y начала и конца

    list<Rocket> listOfUnits1;   // Список юнитов первого игрока
    list<Rocket> listOfUnits2;   // Список юнитов второго игрока
};

#endif // SECTOR_H
