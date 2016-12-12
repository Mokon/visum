/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>

namespace visum {

class LineItem
{

  public:

    LineItem() = default;

    virtual ~LineItem() = default;

    LineItem(const LineItem&) = default;

    LineItem& operator=(const LineItem&) = delete;

    LineItem(LineItem&&) = default;

    LineItem& operator=(LineItem&&) = delete;

  private:

    template<class Archive> void serialize(Archive&)
    {
    }

    friend class cereal::access;

};

}
