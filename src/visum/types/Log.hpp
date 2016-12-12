/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <assert.h>
#include <config.h>
#include <iostream>
#include <glog/logging.h>

namespace visum {

namespace log {

#define CONSOLE() std::cout

#define DEBUG_LOG_IF(...) __extension__ VLOG_IF(__VA_ARGS__)

#define DEBUG_LOG_TRACE_V 1
#define DEBUG_LOG_TRACE_VV 2
#define DEBUG_LOG_TRACE_VVV 3
#define DEBUG_LOG_TRACE_VVVV 4
#define DEBUG_LOG_TRACE_VVVVV 5

static inline void init(int argc, char* argv[])
{
    assert(argc);
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    google::SetStderrLogging(google::INFO);
}

}

}
