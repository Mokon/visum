/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <functional>
#include <visum/types/Time.hpp>
#include <visum/events/actions/Action.hpp>
#include <visum/events/repeats/Repeat.hpp>

namespace visum {

class Transaction;
class CashFlow;

class Event
{
  public:

    Event(const std::string& id, const std::shared_ptr<Repeat>& repeat,
          const std::shared_ptr<Action>& action);

    Event() = delete;

    virtual ~Event() = default;

    Event(const Event&) = delete;

    Event& operator=(const Event&) = delete;

    Event(Event&&) = delete;

    Event& operator=(Event&&) = delete;

    void execute(CashFlow& cashflow);

    TimePoint step(const TimePoint& start, const TimeDuration& amount);

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("id", id),
                //cereal::make_nvp("repeat", repeat),
                //TODO (014) get around unreg poly type
                cereal::make_nvp("action", action));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Event>& construct)
    {
        std::string id;
        std::shared_ptr<Repeat> repeat;
        std::shared_ptr<Action> action;
        ar(id, repeat, action);
        construct(id, repeat, action);
    }

    friend class cereal::access;

  private:

    const std::string id;

    std::shared_ptr<Repeat> repeat;

    std::shared_ptr<Action> action;

};

}
