/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>

namespace visum {

class Statement
{

  public:

    Statement() = default;

    virtual ~Statement() = default;

    Statement(const Statement&) = delete;

    Statement& operator=(const Statement&) = delete;

    Statement(Statement&&) = default;

    Statement& operator=(Statement&&) = delete;

  private:

    template<class Archive> void serialize(Archive&)
    {
    }

    friend class cereal::access;

};

}
