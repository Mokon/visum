/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/entities/common/Bank.hpp>

namespace visum {

Bank::Bank(const std::string& iden)
    : AccountHoldingInstitution(iden)
{
}

std::shared_ptr<Transaction> Bank::depositFunds(const std::string& iden,
                                                const std::shared_ptr<Entity>& entity,
                                                const std::shared_ptr<Account>& account,
                                                const Currency& deposit)
{
    return process(iden, entity, account, deposit, true);
}

std::shared_ptr<Transaction> Bank::withdrawFunds(const std::string& iden,
                                                 const std::shared_ptr<Entity>& entity,
                                                 const std::shared_ptr<Account>& account,
                                                 const Currency& withdrawal)
{
    return process(iden, entity, account, withdrawal, false);
}

}

CEREAL_REGISTER_TYPE(visum::Bank)
