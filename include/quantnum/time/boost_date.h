//
// Created by Alexander Dovzhikov on 2018-12-21.
//

#ifndef QUANTNUM_GREGORIAN_DATE_H
#define QUANTNUM_GREGORIAN_DATE_H

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace quantnum {

class boost_date {
    typedef boost::gregorian::date date_type;
    typedef boost::gregorian::date_duration duration_type;
public:
    boost_date(): date_(boost::gregorian::day_clock::local_day()) {}
    boost_date(int year, int month, int day): date_(year, month, day) {}

    int day() const { return date_.day(); }
    int month() const { return date_.month(); }
    int year() const { return date_.year(); }

    boost_date operator+(int days) const { return boost_date(date_ + duration_type((long) days)); }
    boost_date operator-(int days) const { return boost_date(date_ - duration_type((long) days)); }

    friend std::ostream& operator<<(std::ostream& out, const boost_date& date);
private:
    explicit boost_date(const date_type& date): date_(date) {}
    boost::gregorian::date date_;
};

} // namespace quantnum

#endif //QUANTNUM_GREGORIAN_DATE_H
