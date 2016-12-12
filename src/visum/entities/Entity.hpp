/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <graph/Graph.hpp>

namespace visum {

class Position;

class Entity
    : public graph::Vertex
{

  public:

    explicit Entity(const std::string& id);

    Entity() = delete;

    virtual ~Entity() = default;

    Entity(const Entity&) = delete;

    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = delete;

    Entity& operator=(Entity&&) = delete;

    virtual const std::list<std::shared_ptr<Position>> getPositions();

    const std::string& getId()
    {
        return id;
    }

  private:

    const std::string id;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Vertex",
                                 cereal::base_class<graph::Vertex>(this)),
                cereal::make_nvp("id", id));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Entity>& construct)
    {
        std::string iden;
        ar(iden);
        construct(iden);
    }

    friend class cereal::access;

};

}
