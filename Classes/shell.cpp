#include "shell.h"

shell::shell()
{

}

shell::shell(coordinate_X_Y start, coordinate_X_Y finish){
    this->start = start;
    this->finish = finish;
}
coordinate_X_Y shell::get_start(){
    return start;
}
coordinate_X_Y shell::get_finish(){
    return finish;
}
