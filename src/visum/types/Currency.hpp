/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cereal/archives/json.hpp>
#include <visum/types/Displayable.hpp>
#include <stdexcept>
#include <stdint.h>

namespace visum {

class Currency
    : public Displayable
{

  public:

    class CodeMismatch
        : public std::runtime_error
    {
  public:
        explicit CodeMismatch(const std::string& err)
            : std::runtime_error(err)
        {
        }

        CodeMismatch() = delete;

        virtual ~CodeMismatch() = default;

        CodeMismatch(const CodeMismatch&) = delete;

        CodeMismatch& operator=(const CodeMismatch&) = delete;

        CodeMismatch(CodeMismatch&&) = default;

        CodeMismatch& operator=(CodeMismatch&&) = delete;

    };

    enum Code {
        USD /* amount => cents */
    };

    Currency(const int64_t amount, const Code code);

    Currency() = delete;

    ~Currency() = default;

    Currency(const Currency&) = default;

    Currency& operator=(const Currency&) = default;

    Currency(Currency&&) = default;

    Currency& operator=(Currency&&) = default;

    Currency operator+(const Currency& x);

    Currency operator-(const Currency& x);

    Currency& operator+=(const Currency& x);

    Currency& operator-=(const Currency& x);

    virtual std::ostream& out(std::ostream& stm) const override;

  private:

    inline void check(const Currency& x) const;

    int64_t amount;

    Code code;

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("amount", amount),
                cereal::make_nvp("code", code));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Currency>& construct)
    {
        int64_t amount;
        Code code;
        ar(amount, code);
        construct(amount, code);
    }

    friend class cereal::access;

};

}
