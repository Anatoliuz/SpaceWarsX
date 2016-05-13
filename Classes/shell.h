#ifndef SHELL_H
#define SHELL_H

#include <coordinate_x_y.h>

//Класс снарядов (необходим для отрисовки выстрелов)
class shell
{
public:
    shell();
    shell(coordinate_X_Y start, coordinate_X_Y finish);

private:
    coordinate_X_Y start;    // Координата начала выстрела
    coordinate_X_Y finish;   // Координата конца выстрела
};

#endif // SHELL_H
