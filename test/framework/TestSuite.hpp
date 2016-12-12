/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <gtest/gtest.h>

namespace test {

class TestSuite
    : public ::testing::Test
{
  public:

    TestSuite() = default;

    virtual ~TestSuite() = default;

    TestSuite(const TestSuite&) = delete;

    TestSuite& operator=(const TestSuite&) = delete;

    TestSuite(TestSuite&&) = delete;

    TestSuite& operator=(TestSuite&&) = delete;

    virtual void setupTest();

    virtual void tearDownTest();

    virtual void SetUp() override final;

    virtual void TearDown() override final;

    static void SetUpTestCase();

    static void TearDownTestCase();
};

}
