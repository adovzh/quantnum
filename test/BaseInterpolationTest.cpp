//
// Created by Alexander Dovzhikov on 8/4/18.
//
#include <gtest/gtest.h>
#include <LinearInterpolation.h>
#include <PolynomialInterpolation.h>
#include <SplineInterpolation.h>

namespace QN = quantnum;


TEST(BaseInterpolation, Linear) { // NOLINT
    double xs[] = { 1.0, 2.0, 3.0 };
    double ys[] = { 2.0, 3.0, 4.0 };
    QN::Vector xv(3, xs);
    QN::Vector yv(3, ys);
    QN::LinearInterpolation lin(xv, yv);
    ASSERT_DOUBLE_EQ(3.6, lin.interpolate(2.6));
    ASSERT_DOUBLE_EQ(2.7, lin.interpolate(1.7));
}

TEST(BaseInterpolation, TSLinear) { // NOLINT
    double xs[] = { 0.002739726027397, 0.082191780821918, 0.501369863013699 };
    double ys[] = { 0.014999691789245, 0.016788411762192, 0.017423673870393 };
    QN::Vector xv(3, xs);
    QN::Vector yv(3, ys);
    QN::LinearInterpolation lin(xv, yv);

    double gridx[] = { 0.027397260273973, 0.054794520547945, 0.082191780821918,
                       0.109589041095890, 0.136986301369863, 0.164383561643836,
                       0.191780821917808, 0.219178082191781, 0.246575342465753,
                       0.273972602739726, 0.301369863013699, 0.328767123287671,
                       0.356164383561644, 0.383561643835616, 0.410958904109589,
                       0.438356164383562, 0.465753424657534, 0.493150684931507 };

    double gridy[] = { 0.015554811780850, 0.016171611771521, 0.016788411762192,
                       0.016829932161421, 0.016871452560650, 0.016912972959878,
                       0.016954493359107, 0.016996013758336, 0.017037534157565,
                       0.017079054556794, 0.017120574956022, 0.017162095355251,
                       0.017203615754480, 0.017245136153709, 0.017286656552938,
                       0.017328176952166, 0.017369697351395, 0.017411217750624 };

    for (std::size_t i = 0; i < 18; i++)
        ASSERT_NEAR(gridy[i], lin.interpolate(gridx[i]), 1e-12);
}

TEST(BaseInterpolation, TSPolynomial) { // NOLINT
    QN::Vector xs = { 1.0, 2.0, 3.0 };
    QN::Vector ys = { 1.0, 2.0, 1.0 };
    QN::PolynomialInterpolation poly(xs ,ys, 2);

    QN::Vector gridx = { 1.3, 1.7, 2.0, 2.2, 2.5, 2.76, 3.0 };
    QN::Vector gridy = { 1.3, 1.7, 2.0, 1.8, 1.5, 1.24, 1.0 };

    for (std::size_t i = 0; i < gridx.size(); i++)
        ASSERT_NEAR(gridy[i], poly.interpolate(gridx[i]), 1e-12);
}

TEST(BaseInterpolation, TSPolynomial2) { // NOLINT
    QN::Vector xs = { 1.0, 2.0 };
    QN::Vector ys = { 2.0, 3.0 };
    QN::PolynomialInterpolation poly(xs, ys, 2);

    QN::Vector gridx = { 1.3, 1.7, 2.0 };
    QN::Vector gridy = { 2.3, 2.7, 3.0 };

    for (std::size_t i = 0; i < gridx.size(); i++)
        ASSERT_NEAR(gridy[i], poly.interpolate(gridx[i]), 1e-12);
}

TEST(BaseInterpolation, TSSpline) { // NOLINT
    QN::Vector xs = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    QN::Vector ys = { 2.0, 3.0, 5.0, 10.0, 7.0 };
    QN::SplineInterpolation spline(xs, ys);

    QN::Vector gridx = { 1.3, 1.7, 2.0 };
    QN::Vector gridy = { 2.3, 2.7, 3.0 };

    double v = spline.interpolate(1.3);
    std::cout << "v = " << v << std::endl;
    v = spline.interpolate(1.7);
    std::cout << "v = " << v << std::endl;

    v = spline.interpolate(2.3);
    std::cout << "v = " << v << std::endl;
    v = spline.interpolate(2.7);
    std::cout << "v = " << v << std::endl;

    v = spline.interpolate(3.3);
    std::cout << "v = " << v << std::endl;
    v = spline.interpolate(3.7);
    std::cout << "v = " << v << std::endl;

    v = spline.interpolate(4.3);
    std::cout << "v = " << v << std::endl;
    v = spline.interpolate(4.7);
    std::cout << "v = " << v << std::endl;
    v = spline.interpolate(5.0);
    std::cout << "v = " << v << std::endl;
}