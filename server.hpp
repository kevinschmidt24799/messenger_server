//
// Created by Kevin Schmidt on 1/14/22.
//

#ifndef SERVER_CHAT_SERVER_HPP
#define SERVER_CHAT_SERVER_HPP
#include <list>
#include "client.hpp"

class Server
{
    int port_;
    std::list<Client> client_list_;

public:
//    Server() = delete;
//    Server& operator=(Server& other) = delete;
//    Server(Server& other) = delete;

    [[noreturn]] void start();
    Server(int port):port_{port}{};
    void send_message(std::string const & s, Client const & sender);

};

#endif //SERVER_CHAT_SERVER_HPP
