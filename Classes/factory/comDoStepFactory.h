#ifndef COMDOSTEPFACTORY_H
#define COMDOSTEPFACTORY_H

#include <concreteFabrics.h>

template<class T>
class comDoStepFactory : public concreteFactory<T>
{
 public:
    comDoStepFactory(string factoryType_);
    baseCommand<T>* createCommand (T* r, vector<string>& command);
    ~comDoStepFactory();

 private:
    comDoStepFactory();
};

template<class T>
comDoStepFactory<T>::~comDoStepFactory()
{
    if(PRINTONSCREEN) cout << "~comDoStepFactory()\n";
}

template<class T>
comDoStepFactory<T>::comDoStepFactory(string factoryType_)
{
    comDoStepFactory::factoryType = factoryType_; // what???
    if(PRINTONSCREEN) cout << "comDoStepFactory()\n";
}

template<class T>
baseCommand<T>* comDoStepFactory<T>::createCommand (T* r, vector<string>& command)
{
    assert (command[0] == "doStep");

    baseCommand<T>* newcommand = new commandDoStep<T> (r, &T::doStep);
    return newcommand;
}

#endif // COMDOSTEPFACTORY_H
