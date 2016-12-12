/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <visum/server/Daemon.hpp>

namespace visum {

class Server
    : public Daemon
{

  public:

    Server() = delete;

    Server(int argc, char* argv[]);

    virtual ~Server() = default;

    Server(const Server&) = delete;

    Server& operator=(const Server&) = delete;

    Server(Server&&) = delete;

    Server& operator=(Server&&) = delete;

    void run() override;

  private:

    static constexpr const char* simulateUri = "/simulate";

    void simulate();

};

}
