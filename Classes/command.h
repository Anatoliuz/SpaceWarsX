#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <iostream>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <myFunction.h>

using std::cout;
using std::cin;
using std::string;
using std::vector;

template<class Receiver>
class baseCommand
{
 public:
 //   command();
    typedef void (Receiver::* Action)();
    baseCommand  (Receiver& r_, Action a);
    baseCommand  ();
    virtual bool Execute();

 protected:
    Action action;
    Receiver* rec;
};

//=================================================

template<class Receiver>
bool baseCommand<Receiver>::Execute()
{
    (rec ->* action)();
    return true;
}

template<class Receiver>
baseCommand<Receiver>::baseCommand(Receiver &r_, Action a)
{
    rec = r_;
    action = a;
}

template<class Receiver>
baseCommand<Receiver>::baseCommand()
{
    rec = nullptr;
    action = nullptr;
}

#endif // COMMAND_H
