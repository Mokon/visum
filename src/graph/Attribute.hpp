/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/access.hpp>

namespace graph {

class Attribute
{

  public:

    Attribute() = default;

    virtual ~Attribute() = default;

    Attribute(const Attribute&) = delete;

    Attribute& operator=(const Attribute&) = delete;

    Attribute(Attribute&&) = delete;

    Attribute& operator=(Attribute&&) = delete;

  private:

    template<class Archive> void serialize(Archive&)
    {
    }

    friend class cereal::access;

};

}
