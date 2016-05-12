#ifndef SECTOR_H
#define SECTOR_H

#include <list>
#include <unit.h>

using namespace std;


class sector{
public:
    sector();
    sector(double coord_X, double coord_Y, double diff_X, double diff_Y, int numberOfPlayers);

    // Наряду с конструктором сектора, используется для создания всех секторов в конструкторе планеты
    // (Скорее всего конструктор планеты будет немного переписан и этот метод будет убран)
    void changeCoordinates(double start_X, double start_Y, double finish_X, double finish_Y);

    void createUnit1(int planetNumber);   // Создаёт юнит первого игрока в start сектора    (Пока для отладки, но возможно будет)
    void createUnit2(int planetNumber);   // Создаёт юнит второго игрока в finish сектора   (использоваться на постоянной основе)

    void setConnectPlanet_1(int planetNumber);   // Установка номера планеты, с которой соединён этот сектор (Для первой команды)
    void setConnectPlanet_2(int planetNumber);   // Установка номера планеты, с которой соединён этот сектор (Для второй команды)

    coordinate_X_Y getStart();    // Возвращает координаты конца
    coordinate_X_Y getFinish();   // Возвращает координаты начала
    double getDifference_X();     // Возвращает разницу между коодинатой X начала и конца
    double getDifference_Y();     // Возвращает разницу между коодинатой Y начала и конца

    int getConnectPlanet_1();   // Возвращает номер планеты, на которую совершается перелёт из этого сектора первой командой
    int getConnectPlanet_2();   // Возвращает номер планеты, на которую совершается перелёт из этого сектора второй командой

    list<unit>* getMassOfPlayersLists();   // Возвращает массив списков юнитов всех игроков

 private:
    coordinate_X_Y start;    // Координаты начала сектора
    coordinate_X_Y finish;   // Координаты конца сектора
    double differecne_X;     // Разница между коодинатой X начала и конца
    double differecne_Y;     // Разница между коодинатой Y начала и конца

    int connectPlanet_1;   // Номер планеты, на которую совершается перелёт из этого сектора первой командой
    int connectPlanet_2;   // Номер планеты, на которую совершается перелёт из этого сектора второй командой

    list<unit>* massOfPlayersListsOfUnits;   // Массив списков юнитов всех игроков
};

#endif // SECTOR_H
