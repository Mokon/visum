/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/access.hpp>
#include <memory>
#include <visum/types/Currency.hpp>
#include <visum/types/positions/Position.hpp>
#include <stdexcept>
#include <string>

namespace visum {

class Transaction;

class Account
    : public Position
{

  public:

    class NotFound
        : public std::runtime_error
    {
  public:
        explicit NotFound(const std::string& err)
            : std::runtime_error(err)
        {
        }

        NotFound() = delete;

        virtual ~NotFound() = default;

        NotFound(const NotFound&) = delete;

        NotFound& operator=(const NotFound&) = delete;

        NotFound(NotFound&&) = default;

        NotFound& operator=(NotFound&&) = delete;

    };

    Account(const std::string& id, const Currency::Code code);

    Account() = delete;

    virtual ~Account() = default;

    Account(const Account&) = delete;

    Account& operator=(const Account&) = delete;

    Account(Account&&) = delete;

    Account& operator=(Account&&) = delete;

    std::shared_ptr<Transaction> deposit(const std::string& id,
                                         const Currency& amount);

    std::shared_ptr<Transaction> withdraw(const std::string& id,
                                          const Currency& amount);

    virtual std::ostream& out(std::ostream& stm) const override;

    // cppcheck-suppress unusedFunction
    virtual std::string description() const override;

    // cppcheck-suppress unusedFunction
    virtual std::string position() const override;

  private:

    std::string id;

    Currency balance;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Position",
                                 cereal::base_class<visum::Position>(this)),
                cereal::make_nvp("id", id),
                cereal::make_nvp("balance", balance));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Account>& construct)
    {
        std::string iden;
        Currency::Code code;
        ar(iden, code);
        construct(iden, code);
    }

    friend class cereal::access;

};

}
