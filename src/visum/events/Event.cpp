/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/events/Event.hpp>
#include <visum/statements/cashflow/CashFlow.hpp>
#include <visum/types/transactions/Transaction.hpp>

namespace visum {

Event::Event(const std::string& iden, const std::shared_ptr<Repeat>& rpt,
             const std::shared_ptr<Action>& a)
    : id(iden)
    , repeat(rpt)
    , action(a)
{
}

void Event::execute(CashFlow& cashflow)
{
    auto transaction = action->execute(id);
    // TODO (013) optimize to std::moved
    cashflow.add(transaction->getLineItem());
}

TimePoint Event::step(const TimePoint& start,
                      const TimeDuration& amount)
{
    return repeat->repeat(start, amount);
}

}

CEREAL_REGISTER_TYPE(visum::Event)
