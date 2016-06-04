#ifndef COMMANDCREATEBUILDING_H
#define COMMANDCREATEBUILDING_H

template<class Receiver>
class commandCreateBuilding : public baseCommand<Receiver>
{
 public:
    typedef void (Receiver::* createBuilding) (int planetId, int playerId);
    commandCreateBuilding(Receiver *r_, createBuilding a, int planetId_, int playerId_);
    bool Execute();

 private:
    createBuilding action;
    int planetId;
    int playerId;
    //some params
};


template<class Receiver>
bool commandCreateBuilding<Receiver>::Execute()
{
    (commandCreateBuilding::rec ->* action) (planetId, playerId); // ??? shta
    return true;
}

template<class Receiver>
commandCreateBuilding<Receiver>::commandCreateBuilding(Receiver *r_, createBuilding a,
                                                       int planetId_, int playerId_)
{
    commandCreateBuilding::rec = r_; // what?
    action   = a;
    planetId = planetId_;
    playerId = playerId_;
}


#endif // COMMANDCREATEBUILDING_H
