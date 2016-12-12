/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/types/Currency.hpp>

namespace visum {

Currency::Currency(const int64_t amt, const Code c)
    : amount(amt)
    , code(c)
{
}

void Currency::check(const Currency& x) const
{
    if(x.code != code) {
        throw CodeMismatch("operation invalid on currency code mismatch");
    }
}

Currency Currency::operator+(const Currency& x)
{
    check(x);
    return Currency(amount + x.amount, code);
}

Currency Currency::operator-(const Currency& x)
{
    check(x);
    return Currency(amount - x.amount, code);
}

Currency& Currency::operator+=(const Currency& x)
{
    check(x);
    amount += x.amount;
    return *this;
}

Currency& Currency::operator-=(const Currency& x)
{
    check(x);
    amount -= x.amount;
    return *this;
}

std::ostream& Currency::out(std::ostream& stm) const
{
    return stm << amount;
}

}
