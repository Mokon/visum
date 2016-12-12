/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <boost/concept_check.hpp>
#include <config.h>
#include <functional>
#include <visum/server/Daemon.hpp>
#include <visum/types/Log.hpp>

namespace visum {

Daemon::Daemon(int argc, char* argv[])
    : status(EXIT_SUCCESS)
    , state(init)
{
    try {
        log::init(argc, argv);

        LOG(INFO) << PACKAGE_NAME << " " << PACKAGE_COPYRIGHT << std::endl;

        Timer::addSignalHandler(
            std::bind(static_cast<void(Daemon::*) ()>(&Daemon::stop), this));
    } catch(const std::exception& ex) {
        LOG(ERROR) << ex.what() << std::endl;
        status = EXIT_FAILURE;
    } catch (...) {
        LOG(ERROR) << "Caught thrown" << std::endl;
        status = EXIT_FAILURE;
    }
}

Daemon::~Daemon()
{
}

void
Daemon::changeState(State expectedState, State newState)
{
    if (expectedState != state) {
        throw StateException("illegal state");
    }

    state = newState;
}

void Daemon::start()
{
    // TODO (012) global timer service is ugly.
    Timer::startRun();
    changeState(init, starting);
}

void Daemon::stop()
{
    Timer::stopRun();
    changeState(running, stopping);
}

void Daemon::stop(const boost::system::error_code& ec, int sig)
{
    boost::ignore_unused_variable_warning(ec);
    boost::ignore_unused_variable_warning(sig);
    stop();
}

void Daemon::join()
{
    if (state == running) {
        stop();
    }
    Timer::join();
    changeState(stopping, stopped);
}

int Daemon::getStatus() const
{
    return status;
}

void Daemon::setStatus(int newStatus)
{
    status = newStatus;
}

void Daemon::exec()
{
    if (getStatus() == EXIT_SUCCESS) {
        start();
        changeState(starting, running);
        run();
        join();
    }
}

bool
Daemon::isStopping() const
{
    return state == stopping;
}

}
