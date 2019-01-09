//
// Created by Alexander Dovzhikov on 2018-12-22.
//

#include <gtest/gtest.h>
#include <ctime>
#include <quantnum/time/local_date.h>

using namespace quantnum;

TEST(Dates, CreateSimpleDate) { // NOLINT
    local_date date(2018, 12, 21);
    ASSERT_EQ(21, date.day());
    ASSERT_EQ(12, date.month());
    ASSERT_EQ(2018, date.year());
}

TEST(Dates, CurrentDate) { // NOLINT
    // expected current date
    time_t cur_time = time(nullptr);
    struct tm tm_time = *localtime(&cur_time);

    // actual current date
    local_date date;

    // compare
    ASSERT_EQ(tm_time.tm_mday, date.day());
    ASSERT_EQ(tm_time.tm_mon + 1, date.month());
    ASSERT_EQ(tm_time.tm_year + 1900, date.year());
}
