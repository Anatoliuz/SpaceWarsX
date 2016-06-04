#ifndef COMDOSTEP_H
#define COMDOSTEP_H


#include "command.h"

template<class Receiver>
class commandDoStep : public baseCommand<Receiver>
{
 public:
    typedef void (Receiver::* doStep) ();
    commandDoStep(Receiver *r_, doStep a);
    bool Execute();

 private:
    doStep action;
    //some params
};


template<class Receiver>
bool commandDoStep<Receiver>::Execute()
{
    (commandDoStep::rec ->* action)();
    return true;
}


template<class Receiver>
commandDoStep<Receiver>::commandDoStep(Receiver *r_, doStep a)
{
    commandDoStep::rec = r_; // what?
    action = a;
}


#endif // COMDOSTEP_H
