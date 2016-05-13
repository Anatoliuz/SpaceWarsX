#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <sector.h>
#include <building.h>

class planet{
public:
    double get_planet_radius();
    coordinate_X_Y get_planet_coordinates();
    planet();   // Констуктор по умолчанию создает планету с координатами (0, 0)
    planet(int number, double coord_X, double coord_Y, int numberOfPlayers);

    bool isWar();   // Возвращает true, если идёт война

    void incrementUnitsCount(int playerNumber);   // Увеличивает счётчик кол-ва юнитов на планете для игрока playerNumber
    void decrementUnitsCount(int playerNumber);   // Уменьшает счётчик кол-ва юнитов на планете для игрока playerNumber

    void setOwner(int playerNumber);   // Установка номера хозяина планеты

    int getNumberOfPlanet();   // Возвращает номер планеты
    int getOwner();            // Возвращает номер хозяина планеты

    coordinate_X_Y getCoordinates();   // Возвращает координаты центра планеты
    double getRadiusOfPlanet();        // Возвращает радиус планеты

    int getUnitsCount(int playerNumber);        // Возвращает количество юнитов для игрока playerNumber
    sector** getMassOfSectors();                // Возвращает массив секторов
    vector<building>& getVectorOfBuildings();   // Возвращает вектор зданий

private:
    int numberOfPlanet;    // Номер планеты
    int numberOfPlayers;   // Количество игроков
    int owner;             // Номер хозяина планеты

    coordinate_X_Y coordinate;   // Координаты центра планеты
    double radiusOfPlanet;       // Радиус планеты
    double radiusOfOrbit;        // Радиус орбиты

    int *massOfUnitsCount;                // Массив количества юнитов на планете всех игроков
    sector **massOfSectors;               // Массив секторов
    vector<building> vectorOfBuildings;   // Вектор зданий
};

#endif // PLANET_H

