//
// Created by Alexander Dovzhikov on 2018-12-22.
//

#include <gtest/gtest.h>
#include <ctime>
#include <quantnum/time/local_date.h>

using namespace quantnum;

namespace {

void testDatesAddition(const local_date& actual, int shift, const local_date& expected) {
    local_date lagged = actual + shift;

    ASSERT_EQ(expected.day(), lagged.day());
    ASSERT_EQ(expected.month(), lagged.month());
    ASSERT_EQ(expected.year(), lagged.year());
}

void testDatesSubtraction(const local_date& actual, int shift, const local_date& expected) {
    local_date lagged = actual - shift;

    ASSERT_EQ(expected.day(), lagged.day());
    ASSERT_EQ(expected.month(), lagged.month());
    ASSERT_EQ(expected.year(), lagged.year());
}

}

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

TEST(Dates, Addition) { // NOLINT
    testDatesAddition(local_date(2019, 1, 12), 2, local_date(2019, 1, 14));
    testDatesAddition(local_date(2018, 12, 25), 7, local_date(2019, 1, 1));
}

TEST(Dates, Subtraction) { // NOLINT
    testDatesSubtraction(local_date(2019, 1, 12), 2, local_date(2019, 1, 10));
    testDatesSubtraction(local_date(2019, 1, 5), 7, local_date(2018, 12, 29));
}