/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <visum/events/repeats/Repeat.hpp>

namespace visum {

template <class Unit>
class StartOf
    : public Repeat
{

  public:

    StartOf() = default;

    virtual ~StartOf() = default;

    StartOf(const StartOf&) = delete;

    StartOf& operator=(const Repeat&) = delete;

    StartOf(StartOf&&) = delete;

    StartOf& operator=(StartOf&&) = delete;

    // cppcheck-suppress unusedFunction
    virtual TimePoint repeat(const TimePoint& start,
                             const TimeDuration& amount) override
    {
        auto end = start + amount;
        auto next = round<Unit>(start) + Unit(1);
        if (start <= next and end > next) {
            return next;
        } else {
            return end;
        }
    }

    template<class Archive> void serialize(Archive& archive)
    {
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<StartOf>& construct)
    {
        ar();
        construct();
    }

};

}
