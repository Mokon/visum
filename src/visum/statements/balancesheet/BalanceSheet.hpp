/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <iostream>
#include <list>
#include <visum/statements/Statement.hpp>
#include <visum/statements/balancesheet/PositionLineItem.hpp>
#include <visum/types/Time.hpp>

namespace visum {

class BalanceSheet
    : public Statement
{

  public:

    BalanceSheet(const std::string& time, const std::string& e);

    BalanceSheet(const TimePoint& time, const std::string& e);

    BalanceSheet() = delete;

    virtual ~BalanceSheet() = default;

    BalanceSheet(const BalanceSheet&) = delete;

    BalanceSheet& operator=(const BalanceSheet&) = delete;

    BalanceSheet(BalanceSheet&&) = default;

    BalanceSheet& operator=(BalanceSheet&&) = delete;

    void addPosition(PositionLineItem&& lineItem);

  private:

    std::string entity;

    TimePoint time;

    std::list<PositionLineItem> positions;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("entity", entity),
                cereal::make_nvp("time", to_simple_string(time)),
                cereal::make_nvp("positions", positions));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<BalanceSheet>& construct)
    {
        std::string time;
        std::string id;
        ar(time, id);
        construct(time, id);
    }

    friend class cereal::access;

};

}
