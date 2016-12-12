/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/types/transactions/Transaction.hpp>

namespace visum {

TransactionLineItem Transaction::getLineItem() const
{
    return TransactionLineItem(getDescription(), getTransaction());
}

}

CEREAL_REGISTER_TYPE(visum::Transaction)
