/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/map.hpp>
#include <map>
#include <memory>
#include <graph/BidirectionalEdge.hpp>
#include <graph/Component.hpp>

namespace graph {

class Edge;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
class Vertex
    : public Component
    , public std::enable_shared_from_this<Vertex>
{
#pragma GCC diagnostic pop

  private:

    using Edges = std::map<std::shared_ptr<Vertex>, std::shared_ptr<Edge>>;

  public:

    Vertex();

    virtual ~Vertex() = default;

    Vertex(const Vertex&) = delete;

    Vertex& operator=(const Vertex&) = delete;

    Vertex(Vertex&&) = delete;

    Vertex& operator=(Vertex&&) = delete;

    Edges::iterator edgesToBegin();

    Edges::iterator edgesToEnd();

    Edges::iterator edgesFromBegin();

    Edges::iterator edgesFromEnd();

  protected:

    BidirectionalEdge connectBi(std::shared_ptr<Vertex> other);

    std::shared_ptr<Edge> connectTo(const std::shared_ptr<Vertex>& to);

    std::shared_ptr<Edge> connectFrom(const std::shared_ptr<Vertex>& from);

    const std::shared_ptr<Edge> findTo(const std::shared_ptr<Vertex>& to);

    const std::shared_ptr<Edge> findFrom(const std::shared_ptr<Vertex>& from);

    // provides access for the connect and find functions above
    friend class Graph;

  private:

    Edges edgesTo;

    Edges edgesFrom;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Component",
                                 cereal::base_class<Component>(this)),
                cereal::make_nvp("edgesTo", edgesTo),
                cereal::make_nvp("edgesFrom", edgesFrom));
    }

    friend class cereal::access;

};

}
