/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>
#include <visum/statements/cashflow/TransactionLineItem.hpp>
#include <visum/types/Displayable.hpp>

namespace visum {

class Transaction
    : public Displayable
{

  public:

    Transaction() = default;

    virtual ~Transaction() = default;

    Transaction(const Transaction&) = delete;

    Transaction& operator=(const Transaction&) = delete;

    Transaction(Transaction&&) = delete;

    Transaction& operator=(Transaction&&) = delete;

    virtual std::ostream& out(std::ostream& stm) const override = 0;

    virtual std::string getDescription() const = 0;

    virtual std::string getTransaction() const = 0;

    TransactionLineItem getLineItem() const;

  private:

    template<class Archive> void serialize(Archive&) {
    }

    friend class cereal::access;

};

}
