#include <iostream>
#include "server.hpp"

int main()
{
    Server s{8090};
    s.start();
}
