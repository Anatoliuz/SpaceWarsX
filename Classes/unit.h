#ifndef UNIT_H
#define UNIT_H

#include <coordinate_x_y.h>
#include <movetype.h>
#include <attacktype.h>
#include "cocos2d.h"
//class unit: public cocos2d::Sprite{

class unit{

public:
    unit();
    unit(double X, double Y);   // Конструктор создаёт юнит на координатах X и Y


    void changeCoordinate(double X, double Y);   // Увеличивает координаты юнита на X и Y соответственно

    bool isSectorChange();   // Возвращает true, если юнит должен сменить сектор
    bool isRupture();        // Возвращает true, если появляется разрыв

    void incrementCountSectorChange();   // Увеличивает счётчик смены сектора
    void clearCountSectorChange();       // Обнуляет счётчик смены сектора
    void setKeyRupture(bool rupture);    // Установка ключа разрыва

    int getSpeed();
    moveType getMoveType();

    void writeCoordinates();   // Вывод координат в консоль (для отладки)

private:
    int health;   // Жизни
    int damage;   // Урон
    int speed;    // Скорость

    coordinate_X_Y coordinate;   // Координаты
    moveType unitMoveType;       // Тип движения
    int sectorChange;            // Значение смены сектора
    int countSectorChange;       // Счётчик смены сектора
    bool keyRupture;             // Ключ разрыва
};

#endif // UNIT_H
