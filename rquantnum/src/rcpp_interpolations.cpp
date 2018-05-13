#include <GenericVector.h>
#include <LinearInterpolation.h>
#include <PolynomialInterpolation.h>
#include <SplineInterpolation.h>

#include <algorithm>

#include <Rcpp.h>

using namespace Rcpp;
namespace QN = quantnum;

// [[Rcpp::export]]
NumericVector lininterp(const NumericVector& basex,
                        const NumericVector& basey,
                        const NumericVector& xs) {
    QN::Vector qbasex(basex.size());
    QN::Vector qbasey(basey.size());
    // QN::Vector qxs(xs.size());
    int xs_size = xs.size();
    QN::Vector qys(xs_size);

    std::copy(basex.begin(), basex.end(), &qbasex[0]);
    std::copy(basey.begin(), basey.end(), &qbasey[0]);
    // std::copy(xs.begin(), ys.end(), &xs[0]);

    QN::LinearInterpolation lin(qbasex, qbasey);

    for (std::size_t i = 0; i < xs_size; i++)
        qys[i] = lin.interpolate(xs[i]);

    return NumericVector(&qys[0], &qys[xs_size]);
}

// [[Rcpp::export]]
NumericVector polyinterp(const NumericVector& basex,
                        const NumericVector& basey,
                        int m,
                        const NumericVector& xs) {
    QN::Vector qbasex(basex.size());
    QN::Vector qbasey(basey.size());

    std::copy(basex.begin(), basex.end(), &qbasex[0]);
    std::copy(basey.begin(), basey.end(), &qbasey[0]);

    int xs_size = xs.size();
    QN::Vector qys(xs_size);

    QN::PolynomialInterpolation poly(qbasex, qbasey, m);

    for (int i = 0; i < xs_size; i++)
        qys[i] = poly.interpolate(xs[i]);

    return NumericVector(&qys[0], &qys[xs_size]);
}

// [[Rcpp::export]]
NumericVector splineinterp(const NumericVector& basex,
                          const NumericVector& basey,
                          const NumericVector& xs) {
    QN::Vector qbasex(basex.size());
    QN::Vector qbasey(basey.size());

    std::copy(basex.begin(), basex.end(), &qbasex[0]);
    std::copy(basey.begin(), basey.end(), &qbasey[0]);

    int xs_size = xs.size();
    QN::Vector qys(xs_size);

    QN::SplineInterpolation spl(qbasex, qbasey);

    for (int i = 0; i < xs_size; i++)
        qys[i] = spl.interpolate(xs[i]);

    return NumericVector(&qys[0], &qys[xs_size]);
}
