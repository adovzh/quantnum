//
// Created by Alexander Dovzhikov on 5/5/18.
//

#include <PolynomialInterpolation.h>
#include <LogicError.h>

namespace quantnum {

    double PolynomialInterpolation::interpolateImpl(int jlo, double x) {
        Vector c(static_cast<std::size_t>(m_));
        Vector d(static_cast<std::size_t>(m_));
        int ns = 0;
        double y;

        // move base pointers to position jlo
        const double *xa = &x_[jlo], *ya = &y_[jlo];
        double diff = std::abs(x - xa[0]), dift;

        for (int i = 0; i < m_; i++) { // here we find the index ns of the closest table entry
            if ((dift = std::abs(x - xa[i])) < diff) {
                ns = i;
                diff = dift;
            }

            c[i] = ya[i]; // and initialise the tableau of c and d
            d[i] = ya[i];
        }

        y = ya[ns--]; // initial approximation to y

        for (int m = 1; m < m_; m++) {
            for (int i = 0; i < m_ - m; i++) { // loop and update over c and d
                double ho = xa[i] - x;
                double hp = xa[i + m] - x;
                double w = c[i + 1] - d[i];
                double den;

                // this error can only occur if two input x are identical (to within roundoff)
                if ((den = ho - hp) == 0.0) throw LogicError("Polynomial interpolation error");

                den = w / den;
                c[i] = ho * den;
                d[i] = hp * den;
            }

            y += (error_ = (2 * (ns + 1) < (m_ - m) ? c[ns + 1] : d[ns--]));
        }

        return y;
    }

}