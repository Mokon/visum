/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>
#include <visum/entities/common/AccountHoldingInstitution.hpp>
#include <visum/entities/EntityGraph.hpp>
#include <visum/types/positions/Account.hpp>

namespace visum {

AccountHoldingInstitution::AccountHoldingInstitution(const std::string& iden)
    : Entity(iden)
{
}

std::shared_ptr<Account> AccountHoldingInstitution::createAccount(const std::shared_ptr<Entity>& entity,
                                                                  Currency::Code code)
{
    auto edge = entity->getGraph<EntityGraph>()->connectBi(entity,
                                                           shared_from_this());

    auto account = std::make_shared<Account>(getId(), code);
    auto retA = std::dynamic_pointer_cast<graph::Attribute>(account);
    edge.first->add(retA);
    edge.second->add(retA);

    return account;
}

std::shared_ptr<Transaction>
AccountHoldingInstitution::process(const std::string& iden,
                                   const std::shared_ptr<Entity>& entity,
                                   const std::shared_ptr<Account>& account,
                                   const Currency& amount,
                                   bool deposit)
{
    auto edge = findFrom(entity);
    if (edge->contains(account)) {
        if(deposit) {
            return account->deposit(iden, amount);
        } else {
            return account->withdraw(iden, amount);
        }
    } else {
        throw Account::NotFound("account not found");
    }
}

}

CEREAL_REGISTER_TYPE(visum::AccountHoldingInstitution)
