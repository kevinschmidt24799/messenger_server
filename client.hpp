//
// Created by Kevin Schmidt on 1/14/22.
//

#ifndef SERVER_CHAT_CLIENT_HPP
#define SERVER_CHAT_CLIENT_HPP
#include <thread>

class Client
{
public:
    int name_;

    int socket_;
private:
    class Server & server_;

    //[[noreturn]]void wait_for_message();

public:
    Client() = delete;
    Client& operator=(Client& other) = delete;
    Client(Client& other) = delete;

    Client(int socket, int name, Server & s);
    void send_to_client(std::string const & s);
    void read_message();
};




#endif //SERVER_CHAT_CLIENT_HPP
