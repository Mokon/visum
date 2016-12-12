/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <visum/types/transactions/Transaction.hpp>
#include <visum/types/Currency.hpp>

namespace visum {

class CashTransaction
    : public Transaction
{

  public:

    CashTransaction(const std::string& iden, const Currency& amount);

    CashTransaction() = delete;

    virtual ~CashTransaction() = default;

    CashTransaction(const CashTransaction&) = delete;

    CashTransaction& operator=(const CashTransaction&) = delete;

    CashTransaction(CashTransaction&&) = delete;

    CashTransaction& operator=(CashTransaction&&) = delete;

    virtual std::ostream& out(std::ostream& stm) const override;

    virtual std::string getDescription() const override;

    virtual std::string getTransaction() const override;

  private:

    const std::string id;

    const Currency amount;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("id", id),
                cereal::make_nvp("amount", amount));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<CashTransaction>& construct)
    {
        std::string iden;
        Currency amount(0, Currency::Code::USD);
        ar(iden, amount);
        construct(iden, amount);
    }

    friend class cereal::access;

};

}
