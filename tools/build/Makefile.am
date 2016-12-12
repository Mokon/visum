# Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved

ACLOCAL_AMFLAGS = -I m4
AM_LIBTOOLFLAGS = --silent

if DEBUG
AM_CXXFLAGS = -DDEBUG -g -O0 -fstack-protector-all -static -pg
AM_LDFLAGS = -static -pg
else
AM_CXXFLAGS = -g0 -O3
AM_LDFLAGS =
endif # DEBUG

AM_CXXFLAGS += -Wall -Wextra -std=c++1y -pedantic -Werror -Weffc++ -Wpedantic 
AM_CXXFLAGS += -pedantic-errors -Wundef -Wshadow -Wstrict-aliasing -Wunused
AM_CXXFLAGS += -Wconversion -Wsign-compare -Wsign-conversion -Wdeprecated 
AM_CXXFLAGS += -Wold-style-cast -Wcast-qual -Wcast-align -Wchar-subscripts
AM_CXXFLAGS += -Wtrampolines -Wlogical-op -Wmissing-declarations -Winit-self
AM_CXXFLAGS += -Wmissing-field-initializers -Wparentheses -Wformat=2
AM_CXXFLAGS += -fext-numeric-literals -Wzero-as-null-pointer-constant -Wcomment
AM_CXXFLAGS += -Woverloaded-virtual -Wunused-parameter -I../src -I../test

bin_PROGRAMS = visum_server visum_script visum_test

GRAPH_SOURCES = \
				 ../src/graph/Graph.cpp \
				 ../src/graph/Attribute.cpp \
				 ../src/graph/Component.cpp \
				 ../src/graph/Vertex.cpp \
				 ../src/graph/Edge.cpp

VISUM_SOURCES = \
			   ${GRAPH_SOURCES} \
				 ../src/visum/server/Daemon.cpp \
				 ../src/visum/server/Timer.cpp \
			   ../src/visum/entities/Entity.cpp \
			   ../src/visum/entities/EntityGraph.cpp \
			   ../src/visum/entities/common/AccountHoldingInstitution.cpp \
			   ../src/visum/entities/common/Bank.cpp \
			   ../src/visum/entities/common/CreditCard.cpp \
			   ../src/visum/entities/common/Person.cpp \
			   ../src/visum/events/Event.cpp \
			   ../src/visum/events/actions/Action.cpp \
			   ../src/visum/events/actions/BankDepositFunds.cpp \
			   ../src/visum/events/repeats/Repeat.cpp \
			   ../src/visum/events/repeats/Monthly.cpp \
			   ../src/visum/events/repeats/Once.cpp \
			   ../src/visum/events/repeats/Weekly.cpp \
			   ../src/visum/statements/balancesheet/BalanceSheet.cpp \
			   ../src/visum/statements/balancesheet/PositionLineItem.cpp \
			   ../src/visum/statements/cashflow/CashFlow.cpp \
			   ../src/visum/statements/cashflow/TransactionLineItem.cpp \
			   ../src/visum/types/Currency.cpp \
			   ../src/visum/types/positions/Account.cpp \
			   ../src/visum/types/positions/Position.cpp \
			   ../src/visum/types/transactions/CashTransaction.cpp \
			   ../src/visum/types/transactions/Transaction.cpp

visum_server_SOURCES = \
					  ${VISUM_SOURCES} \
					  ../src/visum/server/Server.cpp \
					  ../src/VisumServerMain.cpp

visum_script_SOURCES = \
							${VISUM_SOURCES} \
							../src/VisumScriptMain.cpp

visum_test_SOURCES = \
							${VISUM_SOURCES} \
							../test/graph/GraphTest.cpp \
							../test/framework/TestSuite.cpp \
							../test/framework/TestMain.cpp
