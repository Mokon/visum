/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/statements/balancesheet/BalanceSheet.hpp>

namespace visum {

BalanceSheet::BalanceSheet(const std::string& t, const std::string& e)
    : BalanceSheet(timeFromString(t), e)
{
}

BalanceSheet::BalanceSheet(const TimePoint& t, const std::string& e)
    : entity(e)
    , time(t)
    , positions()
{
}

void BalanceSheet::addPosition(PositionLineItem&& lineItem)
{
    positions.emplace_back(std::move(lineItem));
}

}
