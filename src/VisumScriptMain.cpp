/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <config.h>
#include <glog/logging.h>
#include <visum/entities/common/Bank.hpp>
#include <visum/entities/common/CreditCard.hpp>
#include <visum/entities/common/Person.hpp>
#include <visum/entities/Entity.hpp>
#include <visum/entities/EntityGraph.hpp>
#include <visum/events/actions/BankDepositFunds.hpp>
#include <visum/events/Event.hpp>
#include <visum/events/repeats/Once.hpp>
#include <visum/types/positions/Account.hpp>

namespace visum {

// TODO (005) remove this exe once we load from a text script

inline void printStaticGraph()
{
    auto eg = std::make_shared<EntityGraph>(localTime());

    auto person = std::make_shared<Person>("person");
    auto bank = std::make_shared<Bank>("bank");
    auto creditcard = std::make_shared<CreditCard>("creditcard");

    eg->graph::Graph::add(person);
    eg->graph::Graph::add(bank);
    eg->graph::Graph::add(creditcard);

    auto checking = bank->createAccount(person);
    auto cc = creditcard->createAccount(person);

    auto once = std::make_shared<Once>(eg->getSimulationTime());
    auto event = std::make_shared<BankDepositFunds>(checking, bank,
                                                    person, Currency(100, Currency::Code::USD));
    auto initialBalance = std::make_shared<Event>("initial balance",
                                                  once, event);
    eg->add(initialBalance);

    cereal::JSONOutputArchive ar(std::cout);
    ar(cereal::make_nvp("entityGraph", eg));
}

}

int main(int argc, char* argv[])
{
    int ret = EXIT_SUCCESS;
    try {
        assert(argc);
        google::InitGoogleLogging(argv[0]);
        google::InstallFailureSignalHandler();
        google::SetStderrLogging(google::INFO);

        visum::printStaticGraph();
    } catch(const std::exception& ex) {
        LOG(ERROR) << ex.what() << std::endl;
        ret = EXIT_FAILURE;
    } catch (...) {
        LOG(ERROR) << "Caught thrown" << std::endl;
        ret = EXIT_FAILURE;
    }

    return ret;
}
