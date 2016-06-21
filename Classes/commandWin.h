#ifndef COMMANDWIN_H
#define COMMANDWIN_H

#include "command.h"

template<class Receiver>
class commandWin : public baseCommand<Receiver>
{
 public:
    typedef void (Receiver::* Win) ();
    commandWin(Receiver *r_, Win a, int winner);
    bool Execute();

 private:
    Win action;
    int winner;
    //some params
};


template<class Receiver>
bool commandWin<Receiver>::Execute()
{
    (commandWin::rec ->* action)(winner);
    return true;
}


template<class Receiver>
commandWin<Receiver>::commandWin(Receiver *r_, Win a, int winner_)
{
    commandWin::rec = r_; // what?
    action = a;
    winner = winner_;
}

#endif // COMMANDWIN_H
