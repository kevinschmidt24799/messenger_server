//
// Created by Kevin Schmidt on 1/14/22.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include "server.hpp"
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <iostream>

[[noreturn]] void Server::start()
{
    int person_count = 0;
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

    while(true)
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
        client_list_.emplace_back(new_socket, ++person_count, *this);
    }
}

void Server::send_message(std::string const & s, Client const & sender)
{
    std::string temp = std::to_string(sender.name_) + ": " + s;
    for(auto & c : client_list_)
    {
        std::cout << "message from: "<<&sender <<" to: "<< &c << '\n';

        if(&c == &sender)
        {
            std::cout << "skipping self-send\n";
            continue;
        }
        c.send_to_client(temp);

    }
}




