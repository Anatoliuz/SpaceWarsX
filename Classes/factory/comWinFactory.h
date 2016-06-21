#ifndef COMWINFACTORY_H
#define COMWINFACTORY_H

#include <concreteFabrics.h>

template<class T>
class comWinFactory : public concreteFactory<T>
{
 public:
    comWinFactory(string factoryType_);
    baseCommand<T>* createCommand (T* r, vector<string>& command);
    ~comWinFactory();

 private:
    comWinFactory();
};

template<class T>
comWinFactory<T>::~comWinFactory()
{
    if(PRINTONSCREEN) cout << "~comWinFactory()\n";
}

template<class T>
comWinFactory<T>::comWinFactory(string factoryType_)
{
    comWinFactory::factoryType = factoryType_; // what???
    if(PRINTONSCREEN) cout << "comWinFactory()\n";
}

template<class T>
baseCommand<T>* comWinFactory<T>::createCommand (T* r, vector<string>& command)
{
    assert (command[0] == "Win");

    int winnerId = strtoInt(command[1]);
    
    baseCommand<T>* newcommand = new commandWin<T> (r, &T::Win, winnerId);
    return newcommand;
}

#endif // COMWINFACTORY_H
