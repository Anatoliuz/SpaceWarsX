#ifndef CLIENT_H
#define CLIENT_H

#include <commandProcessor.h>

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

 private:
    comProcessor<calculationModule>* processor;
    NetWorkModule* netModule;
    calculationModule* calculationMod;
    controller* myController;
    bool active;
    int clientId; // playerId
};

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
    // получаем команды от сервера
    input = "||" + netModule -> getCommandQuery(); // ||_com1_||_com2_||
    processor -> pushCommands(input); // кладем их в процессор команд
    processor -> doCommands(); // выполянем команды
    // получаем действие игрока из контролера
    output = myController -> getAction(); // _com_||
    // отправляем команду на сервер, даже если пустая, чтобы сервер знал, что с нми все ок
    netModule -> sendCommands(output);
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
    processor      = new comProcessor<calculationModule> (calculationMod);
    netModule      = new NetWorkModule();

   // int playerNumber = netModule -> getPlayerNumber();
    calculationMod = new calculationModule(1 /*playerNumber*/);
    myController   = new controller(1 /*playerNumber*/);

    cout << "OK\n";
}

#endif // CLIENT_H
