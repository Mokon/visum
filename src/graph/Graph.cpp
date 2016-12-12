/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <compiler/Assert.hpp>
#include <graph/Graph.hpp>

namespace graph {

Graph::Graph()
    : std::enable_shared_from_this<Graph>()
    , verticies()
    , edges()
{
}

void Graph::add(const std::shared_ptr<Vertex>& vertex)
{
    verticies.push_back(vertex);
    vertex->setGraph(shared_from_this());
}

BidirectionalEdge Graph::connectBi(const std::shared_ptr<Vertex>& to,
                                   const std::shared_ptr<Vertex>& from)
{
    assert (to->getGraph<Graph>().get() == this);
    assert (from->getGraph<Graph>().get() == this);

    auto e1 = from->connectTo(to);
    auto e2 = to->connectTo(from);

    edges.push_back(e1);
    edges.push_back(e2);
    e1->setGraph(shared_from_this());
    e2->setGraph(shared_from_this());

    return std::make_pair(e1, e2);
}

const std::shared_ptr<Edge> Graph::connect(const std::shared_ptr<Vertex>& from,
                                           const std::shared_ptr<Vertex>& to)
{
    auto e = from->connectTo(to);

    edges.push_back(e);
    e->setGraph(shared_from_this());

    return e;
}

}

CEREAL_REGISTER_TYPE(graph::Graph)
