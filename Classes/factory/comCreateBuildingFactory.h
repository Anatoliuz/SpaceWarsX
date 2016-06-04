#ifndef COMCREATENUILDINGFACTORY_H
#define COMCREATENUILDINGFACTORY_H

template<class T>
class comCreateBuildingFactory : public concreteFactory<T>
{
 public:
    comCreateBuildingFactory(string factoryType_);
    baseCommand<T>* createCommand (T* r, vector<string>& command);
    ~comCreateBuildingFactory();

 private:
    comCreateBuildingFactory();
};


template<class T>
comCreateBuildingFactory<T>::~comCreateBuildingFactory()
{
    if(PRINTONSCREEN) cout << "~comCreateBuildingFactory()\n";
}

template<class T>
comCreateBuildingFactory<T>::comCreateBuildingFactory(string factoryType_)
{
    comCreateBuildingFactory::factoryType = factoryType_; // what???
    if(PRINTONSCREEN) cout << "comCreateBuildingFactory()\n";
}

template<class T>
baseCommand<T>* comCreateBuildingFactory<T>::createCommand (T* r, vector<string>& command)
{
    assert (command[0] == "createBuilding");

    int planetId = strtoInt(command[1]);
    int playerId = strtoInt(command[2]);


    baseCommand<T>* newcommand = new commandCreateBuilding<T> (r, &T::createBuilding,
                                                               planetId, playerId);
    return newcommand;
}


#endif // COMCREATENUILDINGFACTORY_H
