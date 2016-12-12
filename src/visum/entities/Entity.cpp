/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <iterator>
#include <visum/entities/Entity.hpp>
#include <visum/types/positions/Position.hpp>

namespace visum {

Entity::Entity(const std::string& iden)
    : id(iden)
{
}

const std::list<std::shared_ptr<Position>> Entity::getPositions()
{
    std::list<std::shared_ptr<Position>> positions;
    for(auto i = edgesFromBegin(); i != edgesFromEnd(); ++i) {
        positions.merge(i->second->find<Position>());
    }
    return positions;
}

}

CEREAL_REGISTER_TYPE(visum::Entity)
