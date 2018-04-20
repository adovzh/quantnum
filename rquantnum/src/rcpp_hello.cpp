#include <GenericVector.h>
#include <LinearInterpolation.h>

#include <algorithm>

#include <Rcpp.h>
using namespace Rcpp;

// This is a simple function using Rcpp that creates an R list
// containing a character vector and a numeric vector.
//
// Learn more about how to use Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//
// and browse examples of code using Rcpp at:
//
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
List rcpp_hello() {
    quantnum::Vector v(2, 1.3);
  CharacterVector x = CharacterVector::create("foo", "bar");
  NumericVector y   = NumericVector::create(0.0, 1.0, v[0], v[1]);
  List z            = List::create(x, y);
  return z;
}

// [[Rcpp::export]]
NumericVector lininterp(const NumericVector& basex,
                        const NumericVector& basey,
                        const NumericVector& xs) {
    quantnum::Vector qbasex(basex.size());
    quantnum::Vector qbasey(basey.size());
    // quantnum::Vector qxs(xs.size());
    int xs_size = xs.size();
    quantnum::Vector qys(xs_size);

    std::copy(basex.begin(), basex.end(), &qbasex[0]);
    std::copy(basey.begin(), basey.end(), &qbasey[0]);
    // std::copy(xs.begin(), ys.end(), &xs[0]);

    quantnum::LinearInterpolation lin(qbasex, qbasey);

    for (std::size_t i = 0; i < xs_size; i++)
        qys[i] = lin.interpolate(xs[i]);

    return NumericVector(&qys[0], &qys[xs_size]);
}
