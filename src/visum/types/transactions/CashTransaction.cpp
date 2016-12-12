/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/types/transactions/CashTransaction.hpp>

namespace visum {

CashTransaction::CashTransaction(const std::string& iden,
                                 const Currency& amt)
    : id(iden)
    , amount(amt)
{
}

std::ostream& CashTransaction::out(std::ostream& stm) const
{
    return stm << id << ": " << amount;
}

std::string CashTransaction::getDescription() const
{
    return id;
}

std::string CashTransaction::getTransaction() const
{
    return amount.display();
}

}

//CEREAL_REGISTER_TYPE(visum::CashTransaction)
