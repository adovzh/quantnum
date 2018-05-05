//
// Created by Alexander Dovzhikov on 6/4/18.
//

#include <iostream>
#include <GenericVector.h>
#include <qndummy.h>
#include <gtest/gtest.h>
#include "TestHelpers.h"

int main(int argc, char** argv) {
    std::cout << "Test Suite: " << qndummy() << std::endl;

    quantnum::Vector vector(3, 0.123);
    quantnum_test::Print("vector", vector);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}