
#include "Network.h"
#include "iostream"
using boost::asio::ip::tcp;
boost::asio::io_service io_service;

Network::Network():
    socket(new tcp::socket(io_service))
{
    boost::asio::io_service io_service;
    //tcp::resolver resolver(io_service);
    //tcp::resolver::query query(SERVER_DOMEN, SERVER_PORT);
    //tcp::resolver::iterator iter = resolver.resolve(query);
    //tcp::endpoint ep = *iter;
    tcp::endpoint ep(boost::asio::ip::address::from_string(SERVER_IP), SERVER_PORT);
    this->socket->connect(ep);
}

void Network::start() {
    boost::asio::streambuf response;
    //boost::asio::read_until(*socket, response, '\n');
    //std::istream response_stream(&response);
    //std::string data;
}

/*
Network::Network():
    socket(new tcp::socket(io_service))
{
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(SERVER_DOMEN, SERVER_PORT);
    tcp::resolver::iterator iter = resolver.resolve(query);
    tcp::endpoint ep = *iter;
    this -> socket -> connect(ep);
}  */
/*
void Network::start() {
    boost::asio::streambuf response;
    boost::asio::read_until(*socket, response, '\n');
    std::istream response_stream(&response);
    std::string data;
    std::getline(response_stream, data,';');
    //for(int i = 0; i < data.length(); i++)
        //std::cout<<data[i];
} */

std::string Network::getCommandQuery() {
    boost::asio::read_until(*socket, buf,"\n");
    std::istream response_stream(&buf);
    std::string data;
    std::getline(response_stream, data,'\n');
    return data;
}

std::string Network::getMap() {
    return getCommandQuery();
}


void Network::sendCommands(std::string commandQuery) {
    commandQuery += (std::string)"\n";
    boost::asio::write(*socket, boost::asio::buffer(commandQuery));
}

void Network::stop(){
    socket->close();
}


