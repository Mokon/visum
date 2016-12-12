/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <glog/logging.h>
#include <visum/entities/Entity.hpp>
#include <visum/entities/EntityGraph.hpp>
#include <visum/events/Event.hpp>
#include <visum/statements/balancesheet/BalanceSheet.hpp>
#include <visum/statements/cashflow/CashFlow.hpp>
#include <visum/types/positions/Position.hpp>

namespace visum {

EntityGraph::EntityGraph(const TimePoint& start)
    : time(start)
    , events()
{
}

EntityGraph::EntityGraph(const std::string& start)
    : EntityGraph(timeFromString(start))
{
}

void EntityGraph::add(const std::shared_ptr<Event>& event)
{
    events.insert(event);
}

TimePoint EntityGraph::getSimulationTime()
{
    return time;
}

void EntityGraph::step(const TimeDuration& amount,
                       CashFlow& cashflow)
{
    auto end = time + amount;
    LOG(INFO) << "step in time (" << time << ") += " << amount;

    EventQueue eventQueue;
    for (const auto& event : events) {
        LOG(INFO) << "\tevent step loop " << event;

        auto etime = time;
        auto amountLeft = amount;
        while (etime <= end) {
            LOG(INFO) << "\t\tevent step from " << etime << " to " << end;

            auto lastTime = event->step(etime, amountLeft);
            amountLeft -= lastTime - etime;
            etime = lastTime;

            LOG(INFO) << "\t\tevent step advanced to " << etime;
            if (etime < end) {
                eventQueue.push(std::make_pair(etime, event));
            }
            etime += 1_s;
            amountLeft -= 1_s;
        }
    }

    LOG(INFO) << "\tevent queue execution";
    while (!eventQueue.empty()) {
        auto event = eventQueue.top();
        LOG(INFO) << "\t executing event " << event.second
                  <<  " @ " << event.first;
        event.second->execute(cashflow);
        eventQueue.pop();
    }

    time += amount;
}

void EntityGraph::simulate(const TimePoint& end,
                           const TimeDuration& steps,
                           const std::shared_ptr<Entity>& entity,
                           std::list<CashFlow>& cashflows,
                           std::list<BalanceSheet>& balanceSheets)
{
    while (getSimulationTime() < end) {
        CashFlow cashflow(getSimulationTime(), getSimulationTime() + steps);
        BalanceSheet balanceSheet(getSimulationTime(), entity->getId());

        for (auto pos : entity->getPositions()) {
            balanceSheet.addPosition(PositionLineItem(pos->description(),
                                                      pos->position()));
        }

        step(steps, cashflow);

        cashflows.emplace_back(std::move(cashflow));
        balanceSheets.emplace_back(std::move(balanceSheet));
    }
}

}

CEREAL_REGISTER_TYPE(visum::EntityGraph)
