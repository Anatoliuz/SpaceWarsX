#ifndef COMMOVEFACTORY_H
#define COMMOVEFACTORY_H

#include <factory/concreteFabrics.h>

//==================comMoveFactory============================================

template<class T>
class comMoveFactory : public concreteFactory<T>
{
 public:
    comMoveFactory(string factoryType_);
    baseCommand<T>* createCommand (T* r, vector<string>& command);
    ~comMoveFactory();

 private:
    comMoveFactory();
};

template<class T>
comMoveFactory<T>::~comMoveFactory()
{
    if(PRINTONSCREEN) cout << "~comMoveFactory()\n";
}

template<class T>
comMoveFactory<T>::comMoveFactory(string factoryType_)
{
    comMoveFactory::factoryType = factoryType_; // what???
    if(PRINTONSCREEN) cout << "comMoveFactory()\n";
}

template<class T>
baseCommand<T>* comMoveFactory<T>::createCommand(T *r, vector<string>& command)
{
    assert (!command.empty());
    assert (command[0] == "move");

    int id1 = strtoInt(command[1]);
    int id2 = strtoInt(command[2]);
    int number = strtoInt(command[3]);
    int player = strtoInt(command[4]);
                                                        //важно: фиксированное имя функции move
    baseCommand<T>* newcommand = new commandMove<T> (r, &T::move, id1, id2, number, player);
    return newcommand;
}

#endif // COMMOVEFACTORY_H
