//
// Created by Alexander Dovzhikov on 8/4/18.
//

#include <BaseInterpolation.h>
#include <LogicError.h>

namespace quantnum {

    /*
     * Given a value x, return a value j such that x is (insofar as possible) centered in the subrange
     * x_[j..j+m_-1], where x_ is the stored pointer. The values in x_ must b emonotonic, either
     * increasing or decreasing. The returned value is not less than 0, nor greater than n_-1;
     */
    int BaseInterpolation::locate(const double x) {
        int jl, jm, ju;
        bool asc;

        if (n_ < 2 || m_ < 2 || m_ > n_) throw LogicError("locate size error");

        jl = 0;
        ju = n_-1;
        asc = x_[ju] >= x_[jl];

        while (ju - jl > 1) {
            jm = static_cast<unsigned>(ju + jl) >> 1u;

            if (x > x_[jm] == asc)
                jl = jm;
            else
                ju = jm;
        }

        cor_ = std::abs(static_cast<long>(jl - jsav_)) <= dj_;

        return std::max(0, std::min(n_ - m_, jl - ((m_ - 2) >> 1))); // NOLINT
    }

    /*
     * Given a value x, return a value j such that x is (insofar as possible) centered in the subrange
     * x_[j..j+m_-1], where x_ is a stored pointer. The values in x_ must be monotonic, either
     * increasing or decreasing. The returned value is not less than 0, nor greater than n_-1.
     */
    int BaseInterpolation::hunt(double x) {
        int jl = jsav_, jm, ju, inc = 1;

        if (n_ < 2 || m_ < 2 || m_ > n_) throw LogicError("hunt size error");

        bool asc = x_[n_ - 1] >= x_[0];

        if (jl < 0 || jl > n_ - 1) { // input guess no useful, go immediately to bisection
            jl = 0;
            ju = n_ - 1;
        } else if (x >= x_[jl] == asc) { // hunt up
            for (;;) {
                ju = jl + inc;

                if (ju >= n_ - 1) { // off end of table
                    ju = n_ - 1;
                    break;
                }
                else if (x < x_[ju] == asc) break; // found bracket
                else {
                    jl = ju;
                    inc += inc;
                }
            }
        } else { // hunt down
            ju = jl;

            for (;;) {
                jl = jl - inc;

                if (jl <= 0) { // off end of table
                    jl = 0;
                    break;
                }
                else if (x >= x_[jl] == asc) break; // found bracket
                else {
                    ju = jl;
                    inc += inc;
                }
            }
        }

        while (ju - jl > 1) { // hunt is done, so begin the final bisection phase
            jm = static_cast<unsigned>(ju + jl) >> 1u;

            if (x >= x_[jm] == asc)
                jl = jm;
            else
                ju = jm;
        }

        cor_ = std::abs(static_cast<long>(jl - jsav_)) <= dj_; // decide whether to use hunt or locate next time
        jsav_ = jl;

        return std::max(0, std::min(n_ - m_, jl - ((m_ - 2) >> 1))); // NOLINT
    }

} // namespace quantnum