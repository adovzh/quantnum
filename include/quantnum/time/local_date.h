//
// Created by Alexander Dovzhikov on 2018-12-21.
//

#ifndef QUANTNUM_LOCAL_DATE_H
#define QUANTNUM_LOCAL_DATE_H

#include <iostream>

#ifdef __DATES_BOOST_IMPL
#include "boost_date.h"
namespace quantnum {

typedef boost_date local_date;

} // namespace quantnum
#else
namespace quantnum {
}
#endif

#endif //QUANTNUM_LOCAL_DATE_H
