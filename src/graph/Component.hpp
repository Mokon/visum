/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/set.hpp>
#include <list>
#include <memory>
#include <graph/Attribute.hpp>
#include <set>

namespace graph {

class Graph;

class Component
{

  public:

    Component();

    virtual ~Component() = default;

    Component(const Component&) = delete;

    Component& operator=(const Component&) = delete;

    Component(Component&&) = delete;

    Component& operator=(Component&&) = delete;

    void add(const std::shared_ptr<Attribute>& attribute);

    template<class FAttr> std::list<std::shared_ptr<FAttr>> find() const
    {
        std::list<std::shared_ptr<FAttr>> ret;

        for(auto attr : attributes) {
            auto concrete = std::dynamic_pointer_cast<FAttr>(attr);
            if(concrete) {
                ret.push_back(concrete);
            }
        }

        return ret;
    }

    // cppcheck-suppress unusedFunction
    bool contains(const std::shared_ptr<Attribute>& attr) const
    {
        return attributes.find(attr) != attributes.end();
    }

    void setGraph(const std::shared_ptr<Graph>& g);

    template<class GraphType> std::shared_ptr<GraphType> getGraph() const
    {
        return std::dynamic_pointer_cast<GraphType>(graph);
    }

  private:

    std::shared_ptr<Graph> graph;

    std::set<std::shared_ptr<Attribute>> attributes;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("graph", graph),
                cereal::make_nvp("attributes", attributes));
    }

    friend class cereal::access;

};

}
