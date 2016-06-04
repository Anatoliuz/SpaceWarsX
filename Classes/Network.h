#ifndef NETWORK_H
#define NETWORK_H
#include "boost/asio.hpp"
#define SERVER_DOMEN "spacewarsx.ddns.net"
#define SERVER_IP "172.16.51.77"
#define SERVER_PORT 2002 //server port

using boost::asio::ip::tcp;

class Network {
public:
    Network();
    std::string getMap();
    std::size_t GetId() {
        return Id;
    }
    bool isServerAlive();
 
    void start();
    void sendCommands(std::string commandQuery);
    std::string getCommandQuery();
    void stop(); 
private:
    tcp::socket* socket;
    boost::asio::streambuf buf;
    std::size_t Id;
};

#endif // NETWORK_H
