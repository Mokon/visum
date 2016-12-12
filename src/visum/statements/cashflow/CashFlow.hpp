/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <iostream>
#include <list>
#include <visum/statements/Statement.hpp>
#include <visum/statements/cashflow/TransactionLineItem.hpp>
#include <visum/types/Time.hpp>

namespace visum {

class CashFlow
    : public Statement
{

  public:

    CashFlow(const TimePoint& from, const TimePoint& to);

    CashFlow(const std::string& from, const std::string& to);

    CashFlow() = delete;

    virtual ~CashFlow() = default;

    CashFlow(const CashFlow&) = delete;

    CashFlow& operator=(const CashFlow&) = delete;

    CashFlow(CashFlow&&) = default;

    CashFlow& operator=(CashFlow&&) = delete;

    void add(const TransactionLineItem& transaction);

  private:

    TimePoint from;

    TimePoint to;

    std::list<TransactionLineItem> transactions;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("from", timeToString(from)),
                cereal::make_nvp("to", timeToString(to)),
                cereal::make_nvp("transactions", transactions));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<CashFlow>& construct)
    {
        std::string from;
        std::string to;
        ar(from, to);
        construct(from, to);
    }

    friend class cereal::access;

};

}
