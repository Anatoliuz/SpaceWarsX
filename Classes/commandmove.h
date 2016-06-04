#ifndef COMMANDMOVE_H
#define COMMANDMOVE_H

#include "command.h"

template<class Receiver>
class commandMove : public baseCommand<Receiver>
{
 public:
    typedef void (Receiver::* MoveAction)(int planetId1, int planetId2, int number, int player);
    commandMove(Receiver *r_, MoveAction a, int planetId1, int planetId2, int number, int player);
    bool Execute();

 private:
    MoveAction action;
    int planetId1;
    int planetId2;
    int number;
    int player;
};

template<class Receiver>
bool commandMove<Receiver>::Execute()
{
    (commandMove::rec ->* action)(planetId1, planetId2, number, player); // ??? shta
    return true;
}

template <class Receiver>
commandMove<Receiver>::commandMove(Receiver* r_, MoveAction a, int planetId1_, int planetId2_, int number_, int player_)
{
    //r = r_;
    planetId1 = planetId1_;
    planetId2 = planetId2_;
    number = number_;
    player = player_;
    action = a;
    commandMove::rec = r_;  // ??? shta
}


#endif // COMMANDMOVE_H
