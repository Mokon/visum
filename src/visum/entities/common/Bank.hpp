/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <visum/entities/common/AccountHoldingInstitution.hpp>
#include <visum/types/Currency.hpp>

namespace visum {

class Transaction;

class Bank
    : public AccountHoldingInstitution
{

  public:

    explicit Bank(const std::string& id);

    Bank() = delete;

    virtual ~Bank() = default;

    Bank(const Bank&) = delete;

    Bank& operator=(const Bank&) = delete;

    Bank(Bank&&) = delete;

    Bank& operator=(Bank&&) = delete;

    std::shared_ptr<Transaction> depositFunds(const std::string& id,
                                              const std::shared_ptr<Entity>& entity,
                                              const std::shared_ptr<Account>& account,
                                              const Currency& deposit);

    std::shared_ptr<Transaction> withdrawFunds(const std::string& id,
                                               const std::shared_ptr<Entity>& entity,
                                               const std::shared_ptr<Account>& account,
                                               const Currency& withdrawal);

  private:

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Entity",
                                 cereal::base_class<AccountHoldingInstitution>(this)));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Bank>& construct) {
        std::string id;
        ar(id);
        construct(id);
    }

    friend class cereal::access;

};

}
