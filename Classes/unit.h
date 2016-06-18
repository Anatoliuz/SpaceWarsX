#ifndef UNIT_H
#define UNIT_H

#include <coordinate_x_y.h>
#include <movetype.h>
#include <ribmovetype.h>
#include <attacktype.h>
class unit{
public:
    unit();
    unit(double X, double Y, int planetNumber, int owner_num);

    bool isChange();     // Возвращает true, если юнит должен выйти из ячейки
    bool isRupture();    // Возвращает true, если появляется разрыв
    bool isRecharge();   // Возвращает true, если юнит перезаряжен
    bool isDead();       // Возвращает true, если юнит мёрт

    void incrementCountChange();     // Увеличивает счётчик выхода из текущей ячейки
    void clearCountChange();         // Обнуляет счётчик выхода из текущей ячейки
    void incrementCountRecharge();   // Увеличивает счётчик перезарядки
    void clearCountRecharge();       // Обнуляет счётчик перезарядки

    void setCurrentPlanet(int planetNumber);    // Установка номера текущей планеты
    void setTransportationStatus(int status);   // Установка номера планеты, на которую будет совершён перелет
    void setChange(int change);                 // Установка значения выхода из текущей ячейки
    void setKeyRupture(bool rupture);           // Установка ключа разрыва

    void changeCoordinate(double X, double Y);   // Увеличивает координаты юнита на X и Y соответственно
    void takeDamage(int damage);                 // Юнит получает урон равный damage

    int getHealth();   // Возвращает жизни
    int getSpeed();    // Возвращает скорость
    int getDamage();   // Возвращает урон

    int getCurrentPlanet();          // Возвращает номер текущей планеты
    int getTransportationStatus();   // Возвращает номер планеты, на которую совершается перелёт
    int getChange();                 // Возвращает значение выхода из текущей ячейки

    coordinate_X_Y getCoordinate();   // Возвращает координаты
    moveType getMoveType();           // Возвращает тип движения
    ribMoveType getRibMoveType();     // Возвращает тип движения в ребре
    attackType getAttackType();       // Возвращает тип атаки

    void writeCoordinates();   // Вывод координат в консоль (для отладки)

    coordinate_X_Y get_unit_coordinates();
    int get_unit_height();
    int get_unit_width();
    
    int get_id();
    int get_owner_num();
private:
    int owner_num; 
    
    int health;   // Жизни
    int speed;    // Скорость
    int damage;   // Урон
    int height;    //размер юнита (высота)
    int width;    //размер юнита (ширина)
    int currentPlanet;          // Номер текущей планеты
    int transportationStatus;   // Номер планеты, на которую совершается перелёт
    int change;                 // Значение выхода из текущей ячейки
    int countChange;            // Счётчик выхода из текущей ячейки
    bool keyRupture;            // Ключ разрыва
    int recharge;               // Значение завершения перезарядки
    int countRecharge;          // Счётчик перезарядки

    int internal_id;
    coordinate_X_Y coordinate;     // Координаты
    moveType unitMoveType;         // Тип движения
    ribMoveType unitRibMoveType;   // Тип движения в ребре
    attackType unitAttackType;     // Тип атаки
};

#endif // UNIT_H
