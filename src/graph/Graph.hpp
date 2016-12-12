/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/access.hpp>
#include <list>
#include <memory>
#include <graph/BidirectionalEdge.hpp>
#include <graph/Edge.hpp>
#include <graph/Vertex.hpp>

namespace graph {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
class Graph
    : public std::enable_shared_from_this<Graph>
{
#pragma GCC diagnostic pop

  public:

    Graph();

    virtual ~Graph() = default;

    Graph(const Graph&) = delete;

    Graph& operator=(const Graph&) = delete;

    Graph(Graph&&) = delete;

    Graph& operator=(Graph&&) = delete;

    void add(const std::shared_ptr<Vertex>& vertex);

    BidirectionalEdge connectBi(const std::shared_ptr<Vertex>& v1,
                                const std::shared_ptr<Vertex>& v2);

    const std::shared_ptr<Edge> connect(const std::shared_ptr<Vertex>& from,
                                        const std::shared_ptr<Vertex>& to);

  private:

    std::list<std::shared_ptr<Vertex>> verticies;

    std::list<std::shared_ptr<Edge>> edges;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("verticies", verticies),
                cereal::make_nvp("edges", edges));
    }

    friend class cereal::access;

};

}
