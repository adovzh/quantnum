//
// Created by Alexander Dovzhikov on 2018-12-21.
//

#ifndef QUANTNUM_GREGORIAN_DATE_H
#define QUANTNUM_GREGORIAN_DATE_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include "local_date.h"

namespace quantnum {

class gregorian_date: public local_date {
public:
    gregorian_date(int year, int month, int day): date_(year, month, day) {}
    ~gregorian_date() override = default;

    int day() const override { return date_.day(); }
    int month() const override { return date_.month(); }
    int year() const override { return date_.year(); }

    std::ostream& to_stream(std::ostream& out) const override;
private:
    boost::gregorian::date date_;
};

} // namespace quantnum

#endif //QUANTNUM_GREGORIAN_DATE_H
