//
// Created by Kevin Schmidt on 1/14/22.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include "server.hpp"
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <iostream>
#include <sys/select.h>

[[noreturn]] void Server::start()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    fd_set rd;

    while(true)
    {

        FD_ZERO(&rd);
        FD_SET(server_fd, &rd);
        int max = server_fd;
        for(auto const & c : client_list_)
        {
            if(c.socket_ > max)
            {
                max = c.socket_;
            }
            FD_SET(c.socket_, &rd);
        }

        std::cout << select(max+1, &rd, nullptr, nullptr, nullptr);

        if(FD_ISSET(server_fd, &rd))
        {
            if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                     (socklen_t *) &addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            int flags = 1;
            int r = setsockopt(new_socket, IPPROTO_TCP, TCP_NODELAY, (void *) &flags, sizeof(flags));
            //std::cout << "new connection\n";
            client_list_.emplace_back(new_socket, *this);
        }

        for(auto c = client_list_.begin(); c != client_list_.end(); )
        {
            if(FD_ISSET(c->socket_, &rd))
            {
                if(! c->read_message())
                {
                    send_message("has left", *c);
                    c = client_list_.erase(c);
                    continue;
                }
            }
            c++;
        }

    }
}

void Server::send_message(std::string const & s, Client const & sender)
{
    std::string temp = sender.name_ + ": " + s;
    for(auto & c : client_list_)
    {
        std::cout << "message from: "<<&sender <<" to: "<< &c << '\n';

        if(&c != &sender && !c.name_.empty())
        {
            c.send_to_client(temp);
        }

    }
}




