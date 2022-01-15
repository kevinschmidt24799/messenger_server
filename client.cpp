//
// Created by Kevin Schmidt on 1/14/22.
//

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "client.hpp"
#include "server.hpp"
static constexpr int buffer_size = 1024;

Client::Client(int socket, int name, Server & s)
    : name_(name)
    , socket_(socket)
    , server_(s)
{
    std::cout << "Made Client(" << name_ << ")\n";
}


//[[noreturn]]void Client::wait_for_message()
//{
//    while(true)
//    {
//        char msg [buffer_size];
//        int stored = 0;
//        stored = read(socket_, msg, buffer_size-1);
//        msg[stored]='\0';
//        if(stored == 0) continue;
//        server_.send_message(std::string{msg, (unsigned long) stored}, *this);
//    }
//}

void Client::send_to_client(std::string const & s)
{
    //std::cout << "send_to_client: ";
    int r = send(socket_, s.c_str(), s.length(), 0);
    //std::cout << r << '\n';
}

void Client::read_message()
{
    char msg [buffer_size];
    int stored = 0;
    stored = read(socket_, msg, buffer_size-1);
    msg[stored]='\0';
    if(stored == 0) return;
    server_.send_message(std::string{msg, (unsigned long) stored}, *this);
}
