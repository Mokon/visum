/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>
#include <visum/statements/LineItem.hpp>

namespace visum {

class TransactionLineItem
    : public LineItem
{

  public:

    explicit TransactionLineItem(const std::string& description,
                                 const std::string& lineitem);

    TransactionLineItem() = delete;

    virtual ~TransactionLineItem() = default;

    // TODO (011) Make TransactionLineItem non-copyable
    TransactionLineItem(const TransactionLineItem&) = default;

    TransactionLineItem& operator=(const TransactionLineItem&) = delete;

    TransactionLineItem(TransactionLineItem&&) = default;

    TransactionLineItem& operator=(TransactionLineItem&&) = delete;

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
                                                           cereal::construct<TransactionLineItem>& construct)
    {
        std::string description;
        std::string lineitem;
        ar(description, lineitem);
        construct(description, lineitem);
    }

    friend class cereal::access;

};

}
