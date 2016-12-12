/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <cereal/archives/json.hpp>
#include <fcgio.h>
#include <fcgiapp.h>
#include <glog/logging.h>
#include <iostream>
#include <visum/entities/Entity.hpp>
#include <visum/entities/EntityGraph.hpp>
#include <visum/server/Server.hpp>
#include <visum/statements/balancesheet/BalanceSheet.hpp>
#include <visum/statements/cashflow/CashFlow.hpp>

#if 1 // TODO (005) remove me
#include <visum/entities/common/Bank.hpp>
#include <visum/entities/common/CreditCard.hpp>
#include <visum/entities/common/Person.hpp>
#include <visum/events/Event.hpp>
#include <visum/events/actions/BankDepositFunds.hpp>
#include <visum/events/repeats/Once.hpp>
#include <visum/events/repeats/Weekly.hpp>
#include <visum/events/repeats/Monthly.hpp>
#include <visum/types/positions/Account.hpp>
#endif

namespace visum {

Server::Server(int argc, char* argv[])
    : Daemon(argc, argv)
{
}

void Server::run()
{
    /*auto cin = std::cin.rdbuf();
       auto cout = std::cout.rdbuf();
       auto cerr = std::cerr.rdbuf();

       FCGX_Request request;
       if (FCGX_Init()) {
        LOG(WARNING) << "FCGX_Init Failed" << std::endl;
       }

       FCGX_InitRequest(&request, 0, 0);

       bool accepted = FCGX_Accept_r(&request) >= 0;
       do {
        fcgi_streambuf cinFcgi(request.in);
        fcgi_streambuf coutFcgi(request.out);
        fcgi_streambuf cerrFcgi(request.err);
        if(accepted) {
            std::cin.rdbuf(&cinFcgi);
            std::cout.rdbuf(&coutFcgi);
            std::cerr.rdbuf(&cerrFcgi);
        }

        //std::cout << "Content-type: text/json\r\n"
        //          << "Access-Control-Allow-Origin *\r\n\r\n";

        const auto requestUriServer = getenv("REQUEST_URI");
        const auto requestUri = requestUriServer == NULL ?
            FCGX_GetParam("REQUEST_URI", request.envp) : requestUriServer;

        // TODO (005) once more uris are added move this to a map. *
        if (requestUri != NULL and std::string(requestUri) == simulateUri) {
            simulate();
        } else {
            std::cout << "null";
        }

        FCGX_Finish();
       } while(FCGX_Accept_r(&request) >= 0 and !isStopping());

       std::cin.rdbuf(cin);
       std::cout.rdbuf(cout);
       std::cerr.rdbuf(cerr);
     */
    simulate();
}

void Server::simulate()
{
    auto eg = std::make_shared<EntityGraph>(localTime());

#if 0
    // TODO (005) parse eg to load from in request uri
    std::string input;
    while (!std::cin.fail()) {
        std::string line;
        std::cin >> line;
        input += line;
    }
    std::stringstream ins(input);
    cereal::JSONInputArchive in(ins);
    in(cereal::make_nvp("entityGraph", eg));

    std::shared_ptr<Entity> person = nullptr; // TODO (005) lookup
#else
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

    auto weekly = std::make_shared<Weekly>();
    auto weeklyDeposit = std::make_shared<Event>("weekly deposit",
                                                 weekly, event);

    auto monthly = std::make_shared<Monthly>();
    auto monthlyDeposit = std::make_shared<Event>("monthly deposit",
                                                  monthly, event);
    eg->add(initialBalance);
    eg->add(monthlyDeposit);
    eg->add(weeklyDeposit);
#endif

    std::list<CashFlow> cashflows;
    std::list<BalanceSheet> balanceSheets;

    // TODO (005) determine right way to load these
    TimeDuration simulationDuration = dateDurationToTimeDuration(Weeks(10));
    TimeDuration simulationSteps = dateDurationToTimeDuration(Weeks(2)); //Hours(24);

    eg->simulate(eg->getSimulationTime() + simulationDuration,
                 simulationSteps, person, cashflows, balanceSheets);

    cereal::JSONOutputArchive out(std::cout);
    out(cereal::make_nvp("entityGraph", eg));
    out(cereal::make_nvp("cashflows", cashflows));
    out(cereal::make_nvp("balancesheets", balanceSheets));
}

}
