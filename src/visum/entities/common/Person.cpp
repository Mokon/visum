/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/entities/common/Person.hpp>

namespace visum {

Person::Person(const std::string& iden)
    : Entity(iden)
{
}

}

CEREAL_REGISTER_TYPE(visum::Person)
