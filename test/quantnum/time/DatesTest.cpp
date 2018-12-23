//
// Created by Alexander Dovzhikov on 2018-12-22.
//

#include <gtest/gtest.h>
#include <quantnum/time/gregorian_date.h>

using namespace quantnum;

TEST(Dates, CreateSimpleDate) { // NOLINT
    auto date = make_date(2012, 12, 21);
    ASSERT_EQ(21, date->day());
    ASSERT_EQ(12, date->month());
    ASSERT_EQ(2018, date->year());
}
