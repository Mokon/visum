/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/server/Server.hpp>

int main(int argc, char* argv[])
{
    visum::Server server(argc, argv);
    server.exec();
    return server.getStatus();
}
