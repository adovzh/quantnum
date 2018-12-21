//
// Created by Alexander Dovzhikov on 2018-12-21.
//

#ifndef QUANTNUM_LOCAL_DATE_H
#define QUANTNUM_LOCAL_DATE_H

#include <iostream>

namespace quantnum {

class local_date {
public:
    virtual ~local_date() = default;
    virtual int day() const = 0;
    virtual int month() const = 0;
    virtual int year() const = 0;

    virtual std::ostream& to_stream(std::ostream&) const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const local_date& date) {
    return date.to_stream(out);
}

std::unique_ptr<local_date> make_date(int year, int month, int day);

} // namespace quantnum

#endif //QUANTNUM_LOCAL_DATE_H
