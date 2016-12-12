/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/memory.hpp>
#include <list>
#include <memory>
#include <visum/types/Time.hpp>
#include <graph/Graph.hpp>
#include <queue>
#include <unordered_set>

namespace visum {

class Entity;
class Event;
class CashFlow;
class BalanceSheet;

class EntityGraph
    : public graph::Graph
{

  public:

    EntityGraph() = delete;

    explicit EntityGraph(const std::string& start);

    explicit EntityGraph(const TimePoint& start);

    virtual ~EntityGraph() = default;

    EntityGraph(const EntityGraph&) = delete;

    EntityGraph& operator=(const EntityGraph&) = delete;

    EntityGraph(EntityGraph&&) = delete;

    EntityGraph& operator=(EntityGraph&&) = delete;

    void add(const std::shared_ptr<Event>& event);

    TimePoint getSimulationTime();

    /* Executes step (either forward or backward) on all events in the
     * entity graph. A transaction list is passed in to return the
     * transactions processed during that step. */
    void step(const TimeDuration& amount,
              CashFlow& cashflow);

    void simulate(const TimePoint& end,
                  const TimeDuration& steps,
                  const std::shared_ptr<Entity>& entity,
                  std::list<CashFlow>& cashflows,
                  std::list<BalanceSheet>& balanceSheets);

  private:
    using EventQueue = std::priority_queue<std::pair<TimePoint,
          std::shared_ptr<Event>>>;

    TimePoint time;

    std::unordered_set<std::shared_ptr<Event>> events;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Graph",
                                 cereal::base_class<graph::Graph>(this)),
                //cereal::make_nvp("time", to_simple_string(time)));
                cereal::make_nvp("events", events));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<EntityGraph>& construct)
    {
        std::string start;
        ar(start);
        construct(start);
    }

    friend class cereal::access;

};

}
