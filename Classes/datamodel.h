#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <vector>
#include <includeMechanics.h>
#include <iostream>

using std::vector;

struct dataModel
{
 public:
    dataModel(int numberOfPlayers, int playerId_);

    vector<planet>* planets;
    vector<rib>*    ribs;
    vector<shell>*  shells;
    int numberOfPlayers;
    int playerId;

};



#endif // DATAMODEL_H
