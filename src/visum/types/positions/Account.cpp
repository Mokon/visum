/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <boost/lexical_cast.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/types/positions/Account.hpp>
#include <visum/types/transactions/CashTransaction.hpp>

namespace visum {

Account::Account(const std::string& iden, const Currency::Code code)
    : id(iden)
    , balance(0, code)
{
}

std::shared_ptr<Transaction> Account::deposit(const std::string& iden,
                                              const Currency& amount)
{
    auto transaction = std::make_shared<CashTransaction>(iden, amount);
    balance += amount;
    return transaction;
}

std::shared_ptr<Transaction> Account::withdraw(const std::string& iden,
                                               const Currency& amount)
{
    auto transaction = std::make_shared<CashTransaction>(iden, amount);
    balance -= amount;
    return transaction;
}

std::ostream& Account::out(std::ostream& stm) const
{
    return stm << id << ": " << balance;
}

// cppcheck-suppress unusedFunction
std::string Account::description() const
{
    return id;
}

// cppcheck-suppress unusedFunction
std::string Account::position() const
{
    return balance.display();
}

}

CEREAL_REGISTER_TYPE(visum::Account)
