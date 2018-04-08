//
// Created by Alexander Dovzhikov on 7/4/18.
//

#include <GenericMatrix.h>
#include <gtest/gtest.h>
#include "TestHelpers.h"

namespace QN = quantnum;

TEST(GenericMatrix, EmptyMatrix) { // NOLINT
    QN::Matrix m1(0, 0);
    ASSERT_EQ(0, m1.nrow());
    ASSERT_EQ(0, m1.ncol());

    QN::Matrix m2(0, 1);
    ASSERT_EQ(0, m2.nrow());
    ASSERT_EQ(1, m2.ncol());

    QN::Matrix m3(1, 0);
    ASSERT_EQ(1, m3.nrow());
    ASSERT_EQ(0, m3.ncol());
}

TEST(GenericMatrix, OneByOne) { // NOLINT
    constexpr double val = 3.14;
    QN::Matrix matrix(1, 1);
    matrix[0][0] = val;

    ASSERT_EQ(1, matrix.nrow());
    ASSERT_EQ(1, matrix.ncol());
    ASSERT_DOUBLE_EQ(val, matrix[0][0]);
}

TEST(GenericMatrix, TwoByTwo) { // NOLINT
    constexpr double v1 = 0.1, v2 = 0.2, v3 = 0.3, v4 = 0.4;
    QN::Matrix m(2, 2);
    ASSERT_EQ(2, m.nrow());
    ASSERT_EQ(2, m.ncol());

    m[0][0] = v1;
    m[0][1] = v2;
    m[1][0] = v3;
    m[1][1] = v4;
    ASSERT_EQ(v1, m[0][0]);
    ASSERT_EQ(v2, m[0][1]);
    ASSERT_EQ(v3, m[1][0]);
    ASSERT_EQ(v4, m[1][1]);
}

TEST(GenericMatrix, ConstructFromValue) { // NOLINT
    constexpr std::size_t n = 3, m = 4;
    constexpr double val = 3.14;
    QN::Matrix matrix(n, m, val);

    for (std::size_t i = 0; i < n; i++)
        for (std::size_t j = 0; j < m; j++)
            ASSERT_EQ(val, matrix[i][j]);
}

TEST(GenericMatrix, ConstructFromArray) { // NOLINT
    constexpr double vals[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    QN::Matrix matrix(2, 3, vals);

    ASSERT_EQ(0.1, matrix[0][0]);
    ASSERT_EQ(0.2, matrix[0][1]);
    ASSERT_EQ(0.3, matrix[0][2]);
    ASSERT_EQ(0.4, matrix[1][0]);
    ASSERT_EQ(0.5, matrix[1][1]);
    ASSERT_EQ(0.6, matrix[1][2]);
}

TEST(GenericMatrix, CopyConstruct) { // NOLINT
    constexpr double vals[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    QN::Matrix src(3, 2, vals);
    QN::Matrix dst = src;

    ASSERT_EQ(0.1, dst[0][0]);
    ASSERT_EQ(0.2, dst[0][1]);
    ASSERT_EQ(0.3, dst[1][0]);
    ASSERT_EQ(0.4, dst[1][1]);
    ASSERT_EQ(0.5, dst[2][0]);
    ASSERT_EQ(0.6, dst[2][1]);
}

TEST(GenericMatrix, Assignment) { // NOLINT
    constexpr double vals[] = { 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1 };
    QN::Matrix src(3, 3, vals);
    QN::Matrix dst(2, 2, 2.0);
    ASSERT_TRUE(src != dst);

    dst = src;
    ASSERT_TRUE(src == dst);
}

TEST(GenericMatrix, MoveContructor) { // NOLINT
    constexpr double vals[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    QN::Matrix src(2, 3, vals);
    QN::Matrix matrix(std::move(src));

    ASSERT_EQ(2, matrix.nrow());
    ASSERT_EQ(3, matrix.ncol());

    ASSERT_EQ(0.1, matrix[0][0]);
    ASSERT_EQ(0.2, matrix[0][1]);
    ASSERT_EQ(0.3, matrix[0][2]);
    ASSERT_EQ(0.4, matrix[1][0]);
    ASSERT_EQ(0.5, matrix[1][1]);
    ASSERT_EQ(0.6, matrix[1][2]);

    ASSERT_EQ(0, src.nrow()); // NOLINT
    ASSERT_EQ(0, src.ncol());
}

TEST(GenericMatrix, MoveAssignment) { // NOLINT
    constexpr double vals[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    QN::Matrix src(2, 3, vals);
    QN::Matrix matrix(2, 1, 2.3);

    matrix = std::move(src);

    ASSERT_EQ(2, matrix.nrow());
    ASSERT_EQ(3, matrix.ncol());

    ASSERT_EQ(0.1, matrix[0][0]);
    ASSERT_EQ(0.2, matrix[0][1]);
    ASSERT_EQ(0.3, matrix[0][2]);
    ASSERT_EQ(0.4, matrix[1][0]);
    ASSERT_EQ(0.5, matrix[1][1]);
    ASSERT_EQ(0.6, matrix[1][2]);

    ASSERT_EQ(0, src.nrow()); // NOLINT
    ASSERT_EQ(0, src.ncol());
}

TEST(GenericMatrix, Swap) { // NOLINT
    constexpr double vals[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    constexpr double val = 2.3;
    QN::Matrix src(2, 3, vals);
    QN::Matrix matrix(2, 1, val);

    quantnum_test::swap(src, matrix);

    ASSERT_EQ(2, matrix.nrow());
    ASSERT_EQ(3, matrix.ncol());

    ASSERT_EQ(0.1, matrix[0][0]);
    ASSERT_EQ(0.2, matrix[0][1]);
    ASSERT_EQ(0.3, matrix[0][2]);
    ASSERT_EQ(0.4, matrix[1][0]);
    ASSERT_EQ(0.5, matrix[1][1]);
    ASSERT_EQ(0.6, matrix[1][2]);

    ASSERT_EQ(2, src.nrow());
    ASSERT_EQ(1, src.ncol());
    ASSERT_EQ(val, src[0][0]);
    ASSERT_EQ(val, src[1][0]);
}