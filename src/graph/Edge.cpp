/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <graph/Edge.hpp>
#include <graph/Graph.hpp>
#include <graph/Vertex.hpp>

namespace graph {

Edge::Edge(const std::shared_ptr<Vertex>& f,
           const std::shared_ptr<Vertex>& t)
    : from(f)
    , to(t)
{
}

}

CEREAL_REGISTER_TYPE(graph::Edge)
