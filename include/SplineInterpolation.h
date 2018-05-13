//
// Created by Alexander Dovzhikov on 12/5/18.
//

#ifndef QUANTNUM_SPLINEINTERPOLATION_H
#define QUANTNUM_SPLINEINTERPOLATION_H

#include "BaseInterpolation.h"

namespace quantnum {

    class SplineInterpolation : public BaseInterpolation {
    public:
        SplineInterpolation(const Vector& xs, const Vector& ys);
    protected:
        double interpolateImpl(int jlo, double x) override;
    private:
        Vector d2y; // vector of second derivatives
    };

}

#endif //QUANTNUM_SPLINEINTERPOLATION_H
