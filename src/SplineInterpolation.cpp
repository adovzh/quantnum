//
// Created by Alexander Dovzhikov on 13/5/18.
//

#include <SplineInterpolation.h>
#include <LogicError.h>

namespace quantnum {

    SplineInterpolation::SplineInterpolation(const quantnum::Vector& xs, const quantnum::Vector& ys):
            BaseInterpolation(xs, &ys[0], 2), d2y(xs.size()) {
        Vector phi((std::size_t)n_);
        int i;

        d2y[0] = d2y[n_ - 1] = phi[0] = 0.0;

        for (i = 1; i < n_ - 1; i++) {
            double gamma = (x_[i] - x_[i - 1]) / (x_[i + 1] - x_[i - 1]);
            double beta = 1.0 / (2.0 - gamma * d2y[i - 1]);
            double& p = phi[i];
            p = (y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (y_[i] - y_[i - 1]) / (x_[i] - x_[i - 1]);
            p = beta * (6.0 * p / (x_[i + 1] - x_[i - 1]) - gamma * phi[i - 1]);
            d2y[i] = (1.0 - gamma) * beta;
        }

        for (i = n_ - 2; i > 0; i--) {
            d2y[i] = phi[i] - d2y[i] * d2y[i + 1];
        }
    }

    double SplineInterpolation::interpolateImpl(int jlo, double x) {
        int lo = jlo, hi = jlo + 1;
        double h = x_[hi] - x_[lo];

        if (h == 0) throw LogicError("Error in SplineInterpolarion, x-grid should be different");

        double a = (x_[hi] - x) / h;
        double b = 1.0 - a;

        return a * y_[lo] + b * y_[hi] + ((a * a * a - a) * d2y[lo] + (b * b * b - b) * d2y[hi]) * h * h / 6.0;
    }

}