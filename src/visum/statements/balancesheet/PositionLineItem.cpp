/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <visum/statements/balancesheet/PositionLineItem.hpp>

namespace visum {

PositionLineItem::PositionLineItem(const std::string& d, const std::string& l)
    : description(d)
    , lineitem(l)
{
}

}
