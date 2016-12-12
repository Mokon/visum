/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/statements/cashflow/CashFlow.hpp>

namespace visum {

CashFlow::CashFlow(const TimePoint& f, const TimePoint& t)
    : from(f)
    , to(t)
    , transactions()
{
}

CashFlow::CashFlow(const std::string& f, const std::string& t)
    : CashFlow(timeFromString(f),
               timeFromString(t))
{
}

void CashFlow::add(const TransactionLineItem& transaction)
{
    transactions.emplace_back(transaction);
}

}
