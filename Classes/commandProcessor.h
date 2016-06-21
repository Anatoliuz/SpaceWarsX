#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <vector>
#include <commands.h>
#include "factory.h"

using std::vector;
using std::string;

template<class Receiver>
class comProcessor
{
 public:
    comProcessor(Receiver *r_);
//    comProcessor(const string& commands);
    ~comProcessor();

    void pushCommands(const string& Commands);
    void doCommands();
    void clear();

 private:
 //   vector< vector<string> > data;
    CommandFactory<Receiver>* factory;
    vector< baseCommand<Receiver>* > commands;
    Receiver* r;
    int head; // команды кладутеся в массив и хранятся там
    // head - индекс в массиве, команды до head обработаны
};


template<class Receiver>
void comProcessor<Receiver>::pushCommands(const string& Commands)
{
    if (!Commands.empty()) {
        vector<string> temp;
        vector< vector<string> > tempCommands;
        separate (Commands, "||", temp); // отделение одной команды от другой
        tempCommands.resize(temp.size());
        for (int i = 0; i < temp.size(); i++) {
            separate(temp[i], " ", tempCommands[i]);
        } // || doStep || move 1  2 3 5 ||

        for (int i = 0; i < tempCommands.size(); i++) {
            commands.push_back(factory -> factoryMethod(tempCommands[i]));
        }
    }
}

template<class Receiver>
comProcessor<Receiver>::comProcessor(Receiver* r_)
{
    head = 0;
    r = r_;
    if(PRINTONSCREEN) cout << "comProcessor()\n";
    factory = new CommandFactory<Receiver>(r);
   // commands.resize(4);
}

template<class Receiver>
comProcessor<Receiver>::~comProcessor()
{
    head = 0;
    if(PRINTONSCREEN) cout << "~comProcessor()\n";
    delete factory;
}

template<class Receiver>
void comProcessor<Receiver>::clear()
{
    commands.clear();
}

template<class Receiver>
void comProcessor<Receiver>::doCommands()
{
    for (; head < commands.size(); head++) {
        commands[head] -> Execute();
    }
}


#endif // COMMANDPROCESSOR_H
