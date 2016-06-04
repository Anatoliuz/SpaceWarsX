#ifndef FABRICA_H
#define FABRICA_H

#include <commands.h>
#include <config.h>
#include <factories.h>

// фабрика команд для процессора команд

template<class Receiver>
class CommandFactory
{
 public:
    CommandFactory(Receiver* r_);
    virtual ~CommandFactory();
    virtual baseCommand<Receiver>* factoryMethod(vector<string>& command);

 private:
    Receiver* r;
    concreteFactory<Receiver>** factories;
    int sizeFactory;
};


template<class Receiver>
CommandFactory<Receiver>::~CommandFactory()
{
    if(PRINTONSCREEN) cout << "~CommandFactory()\n";
    for (int i = 0; i < sizeFactory; i++) {
        delete factories[i];
    }
    delete[] factories;
}


template<class Receiver>
CommandFactory<Receiver>::CommandFactory(Receiver* r_)
{
   r = r_;
   factories = new concreteFactory<Receiver>*[1]; // заполнение абстрактной фабрики
   sizeFactory = 3; // кол-во фабрик               конкретными фабриками
   factories[0] = new comMoveFactory<Receiver>          ("move");
   factories[1] = new comDoStepFactory<Receiver>        ("doStep");
   factories[2] = new comCreateBuildingFactory<Receiver>("createBuilding");
   if(PRINTONSCREEN) cout << "abstractCommandFactory()\n";
}


template<class Receiver>
baseCommand<Receiver>* CommandFactory<Receiver>::factoryMethod(vector<string>& command)
{// идентификация команды и создание объекта команды
    for (int i = 0; i < sizeFactory; i++){
        if (factories[i] -> thisFactory(command[0])) {
            return (factories[i] -> createCommand(r, command));
        }
    }
    return NULL;
}


#endif // FABRICA_H
