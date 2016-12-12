/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <visum/types/Time.hpp>

namespace visum {

class Repeat {

  public:

    Repeat() = default;

    virtual ~Repeat() = default;

    Repeat(const Repeat&) = delete;

    Repeat& operator=(const Repeat&) = delete;

    Repeat(Repeat&&) = delete;

    Repeat& operator=(Repeat&&) = delete;

    virtual TimePoint repeat(const TimePoint& start,
                             const TimeDuration& amount) = 0;

    template<class Archive> void serialize(Archive& archive)
    {
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Repeat>& construct)
    {
        ar();
        construct();
    }
};

}
