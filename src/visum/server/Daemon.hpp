/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <visum/server/Timer.hpp>
#include <stdexcept>

namespace visum {

class Daemon
{

  public:

    enum State {
        init,
        starting,
        running,
        stopping,
        stopped
    };

    class StateException
        : public std::runtime_error
    {
  public:
        explicit StateException(const std::string& err)
            : runtime_error(err)
        {
        }

        StateException() = delete;
        ~StateException() = default;
        StateException(const StateException&) = delete;
        StateException& operator=(const StateException&) = delete;
        StateException(StateException&&) = default;
        StateException& operator=(StateException&&) = delete;
    };

    Daemon() = delete;

    Daemon(int argc, char* argv[]);

    virtual ~Daemon();

    Daemon(const Daemon&) = delete;

    Daemon& operator=(const Daemon&) = delete;

    Daemon(Daemon&&) = delete;

    Daemon& operator=(Daemon&&) = delete;

    virtual void start();

    virtual void join();

    virtual void stop();

    virtual void stop(const boost::system::error_code& ec, int sig);

    virtual void run() = 0;

    void exec();

    int getStatus() const;

    void setStatus(int newStatus);

    void changeState(State expectedState, State newState);

    bool isStopping() const;

  private:

    int status;

    State state = init;

};

}
