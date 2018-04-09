//
// Created by Alexander Dovzhikov on 8/4/18.
//

#include <LinearInterpolation.h>

namespace quantnum {

    double LinearInterpolation::interpolateImpl(int j, double x) {
        if (x_[j] == x_[j+1]) return y_[j]; // table is defective, but we can recover
        else return y_[j] + (x - x_[j]) / (x_[j+1] - x_[j]) * (y_[j+1] - y_[j]);
    }

} // namespace quantnum