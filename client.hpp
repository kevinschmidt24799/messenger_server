//
// Created by Kevin Schmidt on 1/14/22.
//

#ifndef SERVER_CHAT_CLIENT_HPP
#define SERVER_CHAT_CLIENT_HPP
#include <thread>

class Client
{
public:
    std::string name_{""};

    int socket_;
private:
    class Server & server_;

public:
    Client() = delete;
    Client& operator=(Client& other) = delete;
    Client(Client& other) = delete;

    Client(int socket, Server & s);
    void send_to_client(std::string const & s);
    bool read_message();
};




#endif //SERVER_CHAT_CLIENT_HPP
