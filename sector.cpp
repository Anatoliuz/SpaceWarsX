#include "sector.h"


sector::sector()
{

}

sector::sector(double coord_X, double coord_Y, double diff_X, double diff_Y)
{
    differecne_X = diff_X;
    differecne_Y = diff_Y;

    start.x = coord_X;
    start.y = coord_Y;
    finish.x = coord_X;
    finish.y = coord_Y;
}

void sector::changeCoordinates(double start_X, double start_Y, double finish_X, double finish_Y){
    start.x += start_X;
    start.y += start_Y;
    finish.x += finish_X;
    finish.y += finish_Y;

    //this->createUnit();   // Создаем по юниту в секторе для отладки (Потом убрать)
}

void sector::createUnit1(){
    Rocket newUnit(start.x, start.y);
    listOfUnits1.push_back(newUnit);
}

void sector::createUnit2(){
    Rocket newUnit(finish.x, finish.y);
    listOfUnits2.push_back(newUnit);
}

double sector::getDifference_X(){
    return differecne_X;
}

double sector::getDifference_Y(){
    return differecne_Y;
}

list<Rocket>& sector::getListOfUnits1(){
    return listOfUnits1;
}

list<Rocket>& sector::getListOfUnits2(){
    return listOfUnits2;
}
