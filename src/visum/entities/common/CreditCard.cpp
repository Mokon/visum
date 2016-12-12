/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/entities/common/CreditCard.hpp>

namespace visum {

CreditCard::CreditCard(const std::string& iden)
    : AccountHoldingInstitution(iden)
{
}

std::shared_ptr<Transaction> CreditCard::makePayment(const std::string& iden,
                                                     const std::shared_ptr<Entity>& entity,
                                                     const std::shared_ptr<Account>& account,
                                                     const Currency& deposit)
{
    return process(iden, entity, account, deposit, true);
}

std::shared_ptr<Transaction> CreditCard::makePurchase(const std::string& iden,
                                                      const std::shared_ptr<Entity>& entity,
                                                      const std::shared_ptr<Account>& account,
                                                      const Currency& withdrawal)
{
    return process(iden, entity, account, withdrawal, false);
}

}

CEREAL_REGISTER_TYPE(visum::CreditCard)
