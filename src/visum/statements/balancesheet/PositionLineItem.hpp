/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <boost/concept_check.hpp>
#include <cereal/archives/json.hpp>
#include <visum/statements/LineItem.hpp>

namespace visum {

class PositionLineItem
    : public LineItem
{

  public:

    explicit PositionLineItem(const std::string& description,
                              const std::string& lineitem);

    PositionLineItem() = delete;

    virtual ~PositionLineItem() = default;

    PositionLineItem(const PositionLineItem&) = default;

    PositionLineItem& operator=(const PositionLineItem&) = delete;

    PositionLineItem(PositionLineItem&&) = default;

    PositionLineItem& operator=(PositionLineItem&&) = delete;

  private:

    const std::string description;

    const std::string lineitem;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("description", description));
        archive(cereal::make_nvp("lineitem", lineitem));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<PositionLineItem>& construct)
    {
        std::string description;
        std::string lineitem;
        ar(description, lineitem);
        construct(description, lineitem);
    }

    friend class cereal::access;

};

}
