/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <graph/Graph.hpp>
#include <graph/Component.hpp>

namespace graph {

Component::Component()
    : graph(nullptr)
    , attributes()
{
}

void Component::add(const std::shared_ptr<Attribute>& attribute)
{
    attributes.emplace(attribute);
}

void Component::setGraph(const std::shared_ptr<Graph>& g)
{
    this->graph = g;
}

}

CEREAL_REGISTER_TYPE(graph::Component)
