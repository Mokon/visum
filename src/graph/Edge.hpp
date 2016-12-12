/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>
#include <memory>
#include <graph/Component.hpp>

namespace graph {

class Vertex;

class Edge
    : public Component
{

  public:

    Edge(const std::shared_ptr<Vertex>& from,
         const std::shared_ptr<Vertex>& to);

    Edge() = delete;

    virtual ~Edge() = default;

    Edge(const Edge&) = delete;

    Edge& operator=(const Edge&) = delete;

    Edge(Edge&&) = delete;

    Edge& operator=(Edge&&) = delete;

  private:

    const std::shared_ptr<Vertex> from;

    const std::shared_ptr<Vertex> to;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Component",
                                 cereal::base_class<Component>(this)),
                cereal::make_nvp("from", from),
                cereal::make_nvp("to", to));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Edge>& construct)
    {
        std::shared_ptr<Vertex> from;
        std::shared_ptr<Vertex> to;
        ar(from, to);
        construct(from, to);
    }

    friend class cereal::access;

};

}
