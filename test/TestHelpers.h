//
// Created by Alexander Dovzhikov on 8/4/18.
//

#ifndef QUANTNUM_TESTHELPERS_H
#define QUANTNUM_TESTHELPERS_H

#include <utility>

namespace quantnum_test {

    template <typename T>
    void swap(T& x, T& y) {
        T tmp(std::move(x));
        x = std::move(y);
        y = std::move(tmp);
    }

} // quantnum_test

#endif //QUANTNUM_TESTHELPERS_H
