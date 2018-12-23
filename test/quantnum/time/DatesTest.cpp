//
// Created by Alexander Dovzhikov on 2018-12-22.
//

#include <gtest/gtest.h>
#include <quantnum/time/local_date.h>

using namespace quantnum;

TEST(Dates, CreateSimpleDate) { // NOLINT
    local_date date(2018, 12, 21);
    ASSERT_EQ(21, date.day());
    ASSERT_EQ(12, date.month());
    ASSERT_EQ(2018, date.year());
}
