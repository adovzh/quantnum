//
// Created by Alexander Dovzhikov on 2018-12-21.
//

#include <quantnum/time/boost_date.h>

namespace quantnum {

std::ostream& operator<<(std::ostream& out, const boost_date& date) {
    return out << date.date_;
}

} // namespace quantnum