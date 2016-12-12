/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <visum/statements/cashflow/TransactionLineItem.hpp>

namespace visum {

TransactionLineItem::TransactionLineItem(const std::string& d,
                                         const std::string& l)
    : description(d)
    , lineitem(l)
{
}

}
