//
// Created by Alexander Dovzhikov on 8/4/18.
//

#ifndef QUANTNUM_LINEARINTERPOLATION_H
#define QUANTNUM_LINEARINTERPOLATION_H

#include <BaseInterpolation.h>

namespace quantnum {

    class LinearInterpolation: public BaseInterpolation {
    public:
        LinearInterpolation(const Vector& xs, const Vector& ys): BaseInterpolation(xs, &ys[0], 2) {}
    protected:
        double interpolateImpl(int jlo, double x) override;
    };

} // namespace quantnum

#endif //QUANTNUM_LINEARINTERPOLATION_H
