/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <framework/Testing.hpp>
#include <graph/Graph.hpp>

namespace test {

Test(TestSuite, Graph)
{
    auto g = std::make_shared<graph::Graph>();

    auto v1 = std::make_shared<graph::Vertex>();
    auto v2 = std::make_shared<graph::Vertex>();
    g->add(v1);
    g->add(v2);

    auto bi = g->connectBi(v1, v2);
    auto uni = g->connect(v1, v2);
}

}
