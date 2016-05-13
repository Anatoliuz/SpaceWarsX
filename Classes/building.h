#ifndef BUILDING_H
#define BUILDING_H

#include <unit.h>

class building{
public:
    building();
    building(coordinate_X_Y coordinate, int leftArea, int rightArea, int numberOfBuilding);

    bool isReadyToCreate();   // Возвращает true, если здание готово к созданию юнита
    bool isDead();            // Возвращает true, если здание уничтожено

    void changeOrbitForCreation();   // Смена орбиты для создания юнита
    void incrementCountCreate();     // Увеличивает счётчика создания юнита
    void clearCountCreate();         // Обнуляет счётчик создания юнита
    void takeDamage(int damage);     // Здание получает урон равный damage

    int getHealth();                  // Возвращет жизни
    int getNumberOfBuilding();        // Возвращет номер здания
    coordinate_X_Y getCoordinate();   // Возвращет координаты здания

    int getOrbitForCreation();   // Возвращает орбиту для создания юнита
    int getLeftArea();           // Возвращает номер левой зоны
    int getRightArea();          // Возвращает номер правой зоны

private:
    int health;                  // Жизни
    int numberOfBuilding;        // Номер здания
    coordinate_X_Y coordinate;   // Координаты здания

    int orbitForCreation;   // Орбита для создания юнита
    int leftArea;           // Номер левой зоны
    int rightArea;          // Номер правой зоны
    int create;             // Значение создания юнита
    int countCreate;        // Счётчик создания юнита
};

#endif // BUILDING_H
