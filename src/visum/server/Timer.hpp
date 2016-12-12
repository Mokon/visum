/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#include <thread>

namespace visum {

class Timer
{

  public:

    /* Constructs a timer not running. */
    Timer();

    /* Destructs the timer. */
    virtual ~Timer();

    Timer(const Timer&) = delete;

    Timer& operator=(const Timer&) = delete;

    Timer(Timer&&) = delete;

    Timer& operator=(Timer&&) = delete;

    /* Starts the timer running for the given amount of time and an unlimited
     * number of times. */
    void start(int milliseconds);

    /* Starts the timer running for the given amount of time and count times. */
    void start(int milliseconds, unsigned int count);

    /* Connects a callback function pointer. */
    void connect(const std::function<void()>& fp);

    /* Calls the callback function pointer. */
    void callback();

    /* Stops the currently running timer. */
    void stop();

    /* A static timer loop that runs all timers. */
    static int run();

    /* Stops the timer loop. */
    static void stopRun(const boost::system::error_code& ec, int sig);

    /* Stops the timer loop. */
    static void stopRun();

    /* Joins the timer loop. */
    static void join();

    /* Starts the timer loop. */
    static void startRun();

    /* Adds a signal handler to the signals. */
    static void addSignalHandler(std::function<
                                     void(const boost::system::error_code& ec, int signal_number)> handler);

  private:

    /* The underlying timer implementation. */
    boost::asio::deadline_timer timer;

    /* The function pointer to be called on timer expiration. */
    std::function<void()> fp;

    /* Whether when start is called the callback will be called and unlimited
     * number of times or a limited number of times. */
    bool unlimited;

    /* If unlimited == false then this value equals the number of times
     * remaining to call the callback on timeout. */
    unsigned int count;

    /* The number of milliseconds for the current timer. */
    int milliseconds;

    // TODO (012) we should really not have this be a global service
    /* An io_service for the timer class. */
    static boost::asio::io_service io;

    /* A boolean flag on whether the ioservice should be running. */
    static bool running;

    /* signal set for sigint and sigterm */
    static boost::asio::signal_set sigs;

    /* A thread controlling all the timers. */
    static std::thread timers;

};

}
