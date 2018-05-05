//
// Created by Alexander Dovzhikov on 5/5/18.
//

#ifndef QUANTNUM_POLYNOMIALINTERPOLATION_H
#define QUANTNUM_POLYNOMIALINTERPOLATION_H

#include <BaseInterpolation.h>

namespace quantnum {

    class PolynomialInterpolation: public BaseInterpolation {
    public:
        PolynomialInterpolation(const Vector& xs, const Vector& ys, int m):
                BaseInterpolation(xs, &ys[0], m), error_(0.0) {}
        double error() const { return error_; }
    protected:
        double interpolateImpl(int jlo, double x) override;
    private:
        double error_;
    };

}

#endif //QUANTNUM_POLYNOMIALINTERPOLATION_H
