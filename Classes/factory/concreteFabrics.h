#ifndef CONCRETEFABRICS_H
#define CONCRETEFABRICS_H

#include <commands.h>
#include <config.h>

//===================concreteFactory==========================================

template<class T>
class concreteFactory // Null factory
{
 public:
    virtual baseCommand<T>* createCommand (T* r, vector<string>& command) = 0;
    virtual bool thisFactory(const string &factoryType_);
    virtual ~concreteFactory();
 protected:
    string factoryType;
};

template<class T>
concreteFactory<T>::~concreteFactory()
{
  //;
}

template<class T>
bool concreteFactory<T>::thisFactory(const string& factoryType_)
{
    return (factoryType == factoryType_);
}

#endif // CONCRETEFABRICS_H
