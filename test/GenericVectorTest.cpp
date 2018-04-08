//
// Created by Alexander Dovzhikov on 7/4/18.
//

#include <GenericVector.h>
#include <gtest/gtest.h>
#include "TestHelpers.h"

namespace QN = quantnum;

namespace quantnum_test {

    template <typename T>
    void Init(QN::GenericVector<T>& v, std::function<T(std::size_t)> ctr) {
        std::size_t i;

        for (i = 0; i < v.size(); i++)
            v[i] = ctr(i);
    }

}

TEST(TestSuite, Test01) { // NOLINT
    ASSERT_EQ(4, 2 * 2);
}

TEST(GenericVector, CreateAndSet) { // NOLINT
    QN::GenericVector<int> v(5);
    QN::GenericVector<int> empty(0);
    std::function<int(std::size_t)> ictr = [](std::size_t i) { return (i + 1) * 2; };

    quantnum_test::Init(v, ictr);
    ASSERT_EQ(5, v.size());
    ASSERT_EQ(2, v[0]);
    ASSERT_EQ(4, v[1]);
    ASSERT_EQ(6, v[2]);
    ASSERT_EQ(8, v[3]);
    ASSERT_EQ(10, v[4]);
}

TEST(GenericVector, CreateEmpty) { // NOLINT
    QN::GenericVector<int> empty(0);

    ASSERT_EQ(0, empty.size());
}


TEST(GenericVector, CreateDoubleAndSet) { // NOLINT
    const std::size_t vec_size = 4;
    QN::Vector nv(vec_size);
    std::function<double(std::size_t)> ctr = [](std::size_t i) -> double { return (i + 1) * 0.1; };

    quantnum_test::Init(nv, ctr);
    ASSERT_EQ(vec_size, nv.size());
    ASSERT_DOUBLE_EQ(0.1, nv[0]);
    ASSERT_DOUBLE_EQ(0.2, nv[1]);
    ASSERT_DOUBLE_EQ(0.3, nv[2]);
    ASSERT_DOUBLE_EQ(0.4, nv[3]);
}

TEST(GenericVector, CopyConstructor) { // NOLINT
    const std::size_t size = 5;
    QN::Vector vector(size);
    std::function<double(std::size_t)> ctr = [](std::size_t i) -> double { return (i + 1) * 0.1; };

    QN::Vector c1 = vector; // NOLINT
    ASSERT_TRUE(vector == c1);
    ASSERT_FALSE(vector != c1);
    ASSERT_TRUE(c1 == vector);
    ASSERT_FALSE(c1 != vector);

    c1[2] = 3.0;
    ASSERT_TRUE(vector != c1);
    ASSERT_FALSE(vector == c1);
    ASSERT_TRUE(c1 != vector);
    ASSERT_FALSE(c1 == vector);
}

TEST(GenericVector, Assignment) { // NOLINT
    const std::size_t size_v = 5;
    const std::size_t size_c = 8;
    std::function<double(std::size_t)> vctr = [](std::size_t i) -> double { return (i + 1) * 0.2; };
    std::function<double(std::size_t)> cctr = [](std::size_t i) -> double { return (i + 1) * 0.3; };

    QN::Vector v1(size_v);
    QN::Vector c1(size_c);

    ASSERT_TRUE(v1 != c1);

    c1 = v1;

    ASSERT_TRUE(v1 == c1);
}

TEST(GenericVector, MoveConstructor) { // NOLINT
    QN::Vector v(6, 0.025);
    QN::Vector c = std::move(v);

    ASSERT_TRUE(v != c); // NOLINT
    ASSERT_EQ(6, c.size());
    ASSERT_EQ(0, v.size());
}

TEST(GenericVector, MoveAssignment) { // NOLINT
    QN::Vector v(6, 0.025);
    QN::Vector c(4, 0.0125);

    ASSERT_TRUE(v != c);

    v = std::move(c);

    ASSERT_TRUE(v != c); // NOLINT
    ASSERT_EQ(4, v.size());
    ASSERT_EQ(0, c.size());
}

TEST(GenericVector, ZeroLength) { // NOLINT
    QN::Vector z1(0);
    ASSERT_EQ(0, z1.size());

    QN::Vector z2(0, 3.14);
    ASSERT_EQ(0, z2.size());

    QN::Vector v1(4, 6.28);
    ASSERT_EQ(4, v1.size());

    v1 = z2;
    ASSERT_EQ(0, v1.size());

    QN::Vector v2(4, 6.38);
    ASSERT_EQ(4, v2.size());

    z1 = v2;
    ASSERT_EQ(4, z1.size());

    quantnum_test::swap(z1, v1);

    ASSERT_EQ(0, z1.size());
    ASSERT_EQ(0, z2.size());
    ASSERT_EQ(4, v1.size());
    ASSERT_EQ(4, v1.size());
}

TEST(GenericVector, CopyFromArray) { // NOLINT
    double ar[] = { 3.1, 2.3, 4.231 };
    QN::Vector v(3, ar);

    ASSERT_EQ(3, v.size());
    ASSERT_DOUBLE_EQ(ar[0], v[0]);
    ASSERT_DOUBLE_EQ(ar[1], v[1]);
    ASSERT_DOUBLE_EQ(ar[2], v[2]);
}

TEST(GenericVector, Resize) { // NOLINT
    const std::size_t size = 5, new_size = 8;

    QN::Vector v(size);
    ASSERT_EQ(size, v.size());

    v.resize(new_size);
    ASSERT_EQ(new_size, v.size());

    v.resize(0);
    ASSERT_EQ(0, v.size());
}

TEST(GenericVector, Assign) { // NOLINT
    const std::size_t size = 5, new_size = 8;
    const double val = 3.14;

    QN::Vector v(size);
    ASSERT_EQ(size, v.size());

    v.assign(new_size, val);
    ASSERT_EQ(new_size, v.size());

    for (std::size_t i = 0; i < v.size(); i++)
        ASSERT_EQ(val, v[i]);

    v.assign(0, val);
    ASSERT_EQ(0, v.size());
}
