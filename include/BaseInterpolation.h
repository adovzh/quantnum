//
// Created by Alexander Dovzhikov on 8/4/18.
//

#ifndef QUANTNUM_BASEINTERPOLATION_H
#define QUANTNUM_BASEINTERPOLATION_H

#include <cmath>
#include "GenericVector.h"

namespace quantnum {

    class BaseInterpolation {
    public:
        double interpolate(double x);
    protected:
        BaseInterpolation(const Vector& x, const double* y, int m);
        virtual double interpolateImpl(int jlo, double x) = 0;

        int locate(double x);
        int hunt(double x);

        int n_, m_;
        int jsav_, dj_;
        bool cor_;
        const double *x_, *y_;
    };

    inline BaseInterpolation::BaseInterpolation(const Vector& x, const double* y, int m):
            n_((int)x.size()), m_(m), jsav_(0), cor_(false), x_(&x[0]), y_(y) {
        dj_ = std::min(1, static_cast<int>(std::pow(n_, 0.25)));
    }

    inline double BaseInterpolation::interpolate(double x) {
        int jlo = cor_ ? hunt(x) : locate(x);
        return interpolateImpl(jlo, x);
    }

} // namespace quantnum

#endif //QUANTNUM_BASEINTERPOLATION_H
