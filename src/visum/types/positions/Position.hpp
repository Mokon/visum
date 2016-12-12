/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/types//Displayable.hpp>
#include <graph/Graph.hpp>

namespace visum {

class Position
    : public graph::Attribute
    , public Displayable
{

  public:

    Position() = default;

    virtual ~Position() = default;

    Position(const Position&) = delete;

    Position& operator=(const Position&) = delete;

    Position(Position&&) = delete;

    Position& operator=(Position&&) = delete;

    virtual std::ostream& out(std::ostream& stm) const override = 0;

    virtual std::string description() const = 0;

    virtual std::string position() const = 0;

  private:

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Attribute",
                                 cereal::base_class<graph::Attribute>(this)));
    }

    friend class cereal::access;

};

}
