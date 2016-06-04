#ifndef DATA_H
#define DATA_H

#include <config.h>
#include <includeMechanics.h>
#include <datamodel.h>

class calcModAdapter
{
 public:
    calcModAdapter(int playerNumber);
    ~calcModAdapter();
    void move (int planetId1, int planetId2, int number, int player);
    void doStep();
    void createBuilding (int planetId, int playerId);

 private:
    dataModel* data;
//    vector<planet> planets;
//    vector<rib>    ribs;
//    vector<shell>  shells;
    calculationMod* calcMod;

    planet& findPlanet (int planetId);
//    int numberOfPlayers;// издержки реализации calculationMod =(
};

#endif // DATA_H
