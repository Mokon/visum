/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

namespace visum {

using TimePoint = boost::posix_time::ptime;

using TimeDuration = boost::posix_time::time_duration;

using DateDuration = boost::gregorian::date_duration;

using Hours = boost::posix_time::hours;

using Seconds = boost::posix_time::seconds;

using Months = boost::gregorian::months;

using Weeks = boost::gregorian::weeks;

using Days = boost::gregorian::days;

using Date = boost::gregorian::date;

using namespace std::chrono_literals;

using namespace boost::gregorian;

// cppcheck-suppress unusedFunction
inline TimeDuration dateDurationToTimeDuration(const DateDuration& dateDuration)
{
    return Hours(dateDuration.days()*24);
}

inline Seconds operator ""_s(unsigned long long s)
{
    return Seconds(static_cast<long>(s));
}

// cppcheck-suppress unusedFunction
inline auto localTime()
{
    return boost::posix_time::second_clock::local_time();
}

template <typename ... Args>
inline auto
timeFromString(Args&&... args)
{
    return boost::posix_time::time_from_string(std::forward<Args>(args) ...);
}

template <typename ... Args>
inline auto
timeToString(Args&&... args)
{
    return boost::posix_time::to_simple_string(std::forward<Args>(args) ...);
}

template <class RoundUnit> inline auto round(const TimePoint &time);

//        roundedDown = TimePoint(time.date(),
//                                RoundUnit(time.time_of_day().hours()));
//        result = TimePoint(time.date(), roundedDown);

template <> inline auto round<Weeks>(const TimePoint &time)
{
    first_day_of_the_week_before fdbf(Monday);

    auto result = TimePoint(fdbf.get_date(time.date()), Seconds(0));
    if (result.date().week_number() != time.date().week_number()) {
        return result + Weeks(1);
    } else {
        return result;
    }
}

template <> inline auto round<Months>(const TimePoint &time)
{
    TimePoint result(Date(time.date().year(), time.date().month(), 1),
                     Seconds(0));
    if (result.date().month() != time.date().month()) {
        return result + Months(1);
    } else {
        return result;
    }
}

}
