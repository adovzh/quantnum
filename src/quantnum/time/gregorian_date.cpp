//
// Created by Alexander Dovzhikov on 2018-12-21.
//

#include <quantnum/time/gregorian_date.h>

namespace quantnum {

std::ostream& gregorian_date::to_stream(std::ostream& out) const {
    return out << date_;
}

} // namespace quantnum