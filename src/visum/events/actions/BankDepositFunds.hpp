/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <memory>
#include <visum/events/actions/Action.hpp>
#include <visum/types/Currency.hpp>

namespace visum {

class Account;
class Bank;
class Entity;

class BankDepositFunds
    : public Action
{
  public:

    BankDepositFunds(const std::shared_ptr<Account>& acc,
                     const std::shared_ptr<Bank>& b, const std::shared_ptr<Entity>& h,
                     const Currency& d)
        : account(acc)
        , bank(b)
        , holder(h)
        , deposit(d)
    {
    }


    BankDepositFunds() = delete;

    virtual ~BankDepositFunds() = default;

    BankDepositFunds(const BankDepositFunds&) = delete;

    BankDepositFunds& operator=(const BankDepositFunds&) = delete;

    BankDepositFunds(BankDepositFunds&&) = delete;

    BankDepositFunds& operator=(BankDepositFunds&&) = delete;

    virtual std::shared_ptr<Transaction> execute(const std::string& id) override
    {
        return bank->depositFunds(id, holder, account, deposit);
    }

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("account", account),
                cereal::make_nvp("bank", bank),
                cereal::make_nvp("holder", holder),
                cereal::make_nvp("deposit", deposit));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<BankDepositFunds>& construct)
    {
        std::shared_ptr<Account> acc;
        std::shared_ptr<Bank> b;
        std::shared_ptr<Entity> h;
        Currency d(0, Currency::Code::USD);
        ar(acc, b, h, d);
        construct(acc, b, h, d);
    }


  private:
    const std::shared_ptr<Account> account;

    const std::shared_ptr<Bank> bank;

    const std::shared_ptr<Entity> holder;

    const Currency deposit;
};

}
