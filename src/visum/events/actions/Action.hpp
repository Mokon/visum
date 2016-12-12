/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>

namespace visum {

class Transaction;

class Action {

  public:

    Action() = default;

    virtual ~Action() = default;

    Action(const Action&) = delete;

    Action& operator=(const Action&) = delete;

    Action(Action&&) = delete;

    Action& operator=(Action&&) = delete;

    virtual std::shared_ptr<Transaction> execute(const std::string& id) = 0;

    template<class Archive> void serialize(Archive& archive)
    {
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Action>& construct)
    {
        ar();
        construct();
    }
};

}
