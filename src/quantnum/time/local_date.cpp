//
// Created by Alexander Dovzhikov on 2018-12-22.
//

#include <quantnum/time/local_date.h>

namespace quantnum {

std::unique_ptr<local_date> make_date(int year, int month, int day) {
#ifdef __DATES_BOOST_IMPL
    return std::make_unique<boost_date>(year, month, day);
#else
    return std::unique_ptr<local_date>();
#endif
}

} // namespace quantnum