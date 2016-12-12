/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <visum/entities/Entity.hpp>
#include <visum/types/Currency.hpp>

namespace visum {

class Account;
class Transaction;

class AccountHoldingInstitution
    : public Entity
{

  public:

    explicit AccountHoldingInstitution(const std::string& id);

    AccountHoldingInstitution() = delete;

    virtual ~AccountHoldingInstitution() = default;

    AccountHoldingInstitution(const AccountHoldingInstitution&) = delete;

    AccountHoldingInstitution& operator=(const AccountHoldingInstitution&) = delete;

    AccountHoldingInstitution(AccountHoldingInstitution&&) = delete;

    AccountHoldingInstitution& operator=(AccountHoldingInstitution&&) = delete;

    std::shared_ptr<Account> createAccount(const std::shared_ptr<Entity>& entity,
                                           Currency::Code code = Currency::Code::USD);

  protected:

    std::shared_ptr<Transaction> process(const std::string& id,
                                         const std::shared_ptr<Entity>& entity,
                                         const std::shared_ptr<Account>& account,
                                         const Currency& amount,
                                         bool deposit);

  private:

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Entity",
                                 cereal::base_class<Entity>(this)));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<AccountHoldingInstitution>& construct)
    {
        std::string id;
        ar(id);
        construct(id);
    }

    friend class cereal::access;

};

}
