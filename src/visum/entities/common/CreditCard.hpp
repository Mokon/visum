/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <visum/entities/common/AccountHoldingInstitution.hpp>
#include <visum/types/Currency.hpp>

namespace visum {

class CreditCard
    : public AccountHoldingInstitution
{

  public:

    explicit CreditCard(const std::string& id);

    CreditCard() = delete;

    virtual ~CreditCard() = default;

    CreditCard(const CreditCard&) = delete;

    CreditCard& operator=(const CreditCard&) = delete;

    CreditCard(CreditCard&&) = delete;

    CreditCard& operator=(CreditCard&&) = delete;

    std::shared_ptr<Transaction> makePayment(const std::string& id,
                                             const std::shared_ptr<Entity>& entity,
                                             const std::shared_ptr<Account>& account,
                                             const Currency& deposit);

    std::shared_ptr<Transaction> makePurchase(const std::string& id,
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
                                                           cereal::construct<CreditCard>& construct)
    {
        std::string id;
        ar(id);
        construct(id);
    }

    friend class cereal::access;

};

}
