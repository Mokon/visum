/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <graph/Edge.hpp>
#include <graph/Graph.hpp>
#include <graph/Vertex.hpp>

namespace graph {

Vertex::Vertex()
    : edgesTo()
    , edgesFrom()
{
}

BidirectionalEdge Vertex::connectBi(const std::shared_ptr<Vertex> other)
{
    return std::make_pair(connectTo(other), connectFrom(other));
}

std::shared_ptr<Edge> Vertex::connectTo(const std::shared_ptr<Vertex>& to)
{
    auto e = std::make_shared<Edge>(shared_from_this(), to);
    edgesFrom[to] = e;
    to->edgesTo[shared_from_this()] = e;
    return e;
}

std::shared_ptr<Edge> Vertex::connectFrom(const std::shared_ptr<Vertex>& from)
{
    auto e = std::make_shared<Edge>(from, shared_from_this());
    edgesTo[from] = e;
    from->edgesFrom[shared_from_this()] = e;
    return e;
}

const std::shared_ptr<Edge> Vertex::findTo(const std::shared_ptr<Vertex>& to)
{
    return edgesTo[to];
}

const std::shared_ptr<Edge> Vertex::findFrom(const std::shared_ptr<Vertex>& from)
{
    return edgesFrom[from];
}

Vertex::Edges::iterator Vertex::edgesToBegin()
{
    return edgesTo.begin();
}

Vertex::Edges::iterator Vertex::edgesToEnd()
{
    return edgesTo.end();
}

Vertex::Edges::iterator Vertex::edgesFromBegin()
{
    return edgesFrom.begin();
}

Vertex::Edges::iterator Vertex::edgesFromEnd()
{
    return edgesFrom.end();
}

}

CEREAL_REGISTER_TYPE(graph::Vertex)
