//
// Created by Kevin Schmidt on 1/14/22.
//

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "client.hpp"
#include "server.hpp"
static constexpr int buffer_size = 1024;

Client::Client(int socket, Server & s)
    : socket_(socket)
    , server_(s)
{
    std::cout << "Made Client(" << name_ << ")\n";
    send_to_client("Welcome to Kevin Chat\nSelect a username: ");
}


void Client::send_to_client(std::string const & s)
{
    //std::cout << "send_to_client: ";
    int r = send(socket_, s.c_str(), s.length(), 0);
    //std::cout << r << '\n';
}

bool Client::read_message()
{

    char msg [buffer_size];
    int stored = 0;
    stored = read(socket_, msg, buffer_size-1);
    msg[stored]='\0';
    if(stored == 0) return false;
    if(name_.empty())
    {
        name_ = msg;
        server_.send_message(name_ + " has joined the chat", *this);
    } else
    {
        server_.send_message(std::string{msg, (unsigned long) stored}, *this);
    }
    return true;
}
