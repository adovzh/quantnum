//
// Created by Alexander Dovzhikov on 8/4/18.
//

#ifndef QUANTNUM_TESTHELPERS_H
#define QUANTNUM_TESTHELPERS_H

#include <utility>
#include <GenericVector.h>

namespace quantnum_test {

    template <typename T>
    void swap(T& x, T& y) {
        T tmp(std::move(x));
        x = std::move(y);
        y = std::move(tmp);
    }

    template <typename T>
    void Print(const char* msg, quantnum::GenericVector<T>& v) {
        std::size_t i;

        std::cout << msg << ": ";

        for (i = 0; i < v.size(); i++)
            std::cout << v[i] << " ";

        std::cout << std::endl;
    }
} // quantnum_test

#endif //QUANTNUM_TESTHELPERS_H
