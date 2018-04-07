//
// Created by Alexander Dovzhikov on 7/4/18.
//

#ifndef QUANTNUM_MATRIX_H
#define QUANTNUM_MATRIX_H

#include <cstddef>
#include <algorithm>

namespace quantnum {

    template <typename T>
    class GenericMatrix {
    public:
        typedef T value_type;

        explicit GenericMatrix(std::size_t n, std::size_t m);
        GenericMatrix(std::size_t n, std::size_t m, const T& a);
        GenericMatrix(std::size_t n, std::size_t m, const T* a);
        ~GenericMatrix() { if (data_ != nullptr) delete[] data_; }

        T*& operator[](std::size_t index) const { return data_[index]; }
        T*& operator[](std::size_t index) { return data_[index]; }

        std::size_t nrow() const { return n_; }
        std::size_t ncol() const { return m_; }
    private:
        void allocate(std::size_t n, std::size_t m);

        std::size_t n_, m_;
        T** data_;
    };

    template <typename T>
    inline GenericMatrix<T>::GenericMatrix(std::size_t n, std::size_t m):
            n_(n), m_(m), data_(n > 0 ? new T*[n] : nullptr) {
        allocate(n, m);
    }

    template<typename T>
    inline GenericMatrix<T>::GenericMatrix(std::size_t n, std::size_t m, const T& a):
            n_(n), m_(m), data_(n > 0 ? new T*[n] : nullptr) {
        allocate(n, m);
        std::fill(data_[0], data_[0] + n * m, a);
    }

    template<typename T>
    GenericMatrix<T>::GenericMatrix(std::size_t n, std::size_t m, const T* a):
            n_(n), m_(m), data_(n > 0 ? new T*[n] : nullptr) {
        allocate(n, m);
        std::copy(a, a + n * m, data_[0]);
    }

    template <typename T>
    inline void GenericMatrix<T>::allocate(std::size_t n, std::size_t m) {
        const std::size_t size = n * m;
        T* p = data_ != nullptr ? new T[size] : nullptr;
        T** q = data_;

        while (n-- > 0) {
            *q++ = p;
            p += m;
        }
    }

    typedef GenericMatrix<double> Matrix;

} // namespace quantnum

#endif //QUANTNUM_MATRIX_H
