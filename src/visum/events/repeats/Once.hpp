/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <visum/events/repeats/Repeat.hpp>

namespace visum {

class Once
    : public Repeat
{

  public:

    explicit Once(const TimePoint& t) : time(t) {
    }

    Once() = delete;

    virtual ~Once() = default;

    Once(const Once&) = delete;

    Once& operator=(const Repeat&) = delete;

    Once(Once&&) = delete;

    Once& operator=(Once&&) = delete;

    // cppcheck-suppress unusedFunction
    virtual TimePoint repeat(const TimePoint& start,
                             const TimeDuration& amount) override
    {
        auto end = start + amount;
        if (start <= time and end > time) {
            return time;
        } else {
            return end;
        }
    }

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("time", time));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Once>& construct)
    {
        TimePoint t;
        ar(t);
        construct(t);
    }

  private:

    TimePoint time;

};

}
