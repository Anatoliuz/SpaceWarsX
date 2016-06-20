#ifndef CLIENT_H
#define CLIENT_H

#include <commandProcessor.h>
//*
#include <vector>
#include <planet.h>
#include <rib.h>
#include <shell.h>
//*
#include <includeMechanics.h>
#include <controller.h>

// класс, который осуществляет работу всех модулей клиентской стороны
template<class calculationModule, class NetWorkModule>
class client
{
 public:
    client();
    ~client();
    void doWork();
    controller* getContoller();
    vector<unit> getVectorOfUnits(vector<planet> vectorOfPlanets, vector<rib> vectorOfRibs, int numbOfPlayers);
    calculationModule* calculationMod;
 private:
    comProcessor<calculationModule>* processor;
    NetWorkModule* netModule;
  //  calculationModule* calculationMod;
    controller* myController;
    bool active;
    int clientId; // playerId
};

template<class calculationModule, class NetWorkModule>
vector<unit> client<calculationModule, NetWorkModule>::getVectorOfUnits(vector<planet> vectorOfPlanets, vector<rib> vectorOfRibs, int numbOfPlayers)
{
    return calculationMod->getVectorOfUnits(vectorOfPlanets, vectorOfRibs, numbOfPlayers);
}

template<class calculationModule, class NetWorkModule>
controller* client<calculationModule, NetWorkModule>::getContoller()
{
    return myController;
}


template<class calculationModule, class NetWorkModule>
void client<calculationModule, NetWorkModule>::doWork()
{  // ф-я шага клиента, принимает от сервера,
   // вызывает обработку команд(в которых вызывается перерасчет), перерисовку, отправку сообщений серверу
   // наверное все
    string input  = "";
    string output = "";
    // получаем действие игрока из контролера
    output = myController -> getAction();// + " doStep ||"; || _com_ || or|| WIN player0 ||
    // отправляем команду на сервер, даже если пустая, чтобы сервер знал, что с нми все ок
    netModule -> sendCommands(output);    // получаем команды от сервера
    input = "||" + netModule -> getCommandQuery();// + "|| doStep ||"; // ||_com1_||_com2_||
    processor -> pushCommands(input); // кладем их в процессор команд
    processor -> doCommands(); // выполянем команды
 
}

template<class calculationModule, class NetWorkModule>
client<calculationModule, NetWorkModule>::~client()
{
    delete processor;
    delete netModule;
    delete calculationMod;
    delete myController;
}

template<class calculationModule, class NetWorkModule>
client<calculationModule, NetWorkModule>::client()
{
    active = false;
    netModule      = new NetWorkModule();

    int playerNumber = netModule -> getPlayerNumber();
    calculationMod = new calculationModule(playerNumber);
    processor = new comProcessor<calculationModule>(calculationMod);
    myController   = new controller(playerNumber);

    cout << "OK\n";
}

#endif // CLIENT_H
