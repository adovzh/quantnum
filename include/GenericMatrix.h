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
        ~GenericMatrix();

        GenericMatrix(const GenericMatrix& that);
        GenericMatrix(GenericMatrix&& that) noexcept;
        GenericMatrix& operator=(const GenericMatrix& that);
        GenericMatrix& operator=(GenericMatrix&& that) noexcept;
        bool operator==(const GenericMatrix& that) const;
        bool operator!=(const GenericMatrix& that) const { return !(*this == that); }

        T*& operator[](std::size_t index) const { return data_[index]; }
        T*& operator[](std::size_t index) { return data_[index]; }

        std::size_t nrow() const { return n_; }
        std::size_t ncol() const { return m_; }

        void resize(std::size_t n, std::size_t m);
        void assign(std::size_t n, std::size_t m, const T& a);
    private:
        void allocate(std::size_t n, std::size_t m);
        std::size_t size() const { return n_ * m_; }

        std::size_t n_, m_;
        T** data_;
    };

    template <typename T>
    GenericMatrix<T>::GenericMatrix(std::size_t n, std::size_t m):
            n_(n), m_(m), data_(n > 0 ? new T*[n] : nullptr) {
        allocate(n, m);
    }

    template<typename T>
    GenericMatrix<T>::GenericMatrix(std::size_t n, std::size_t m, const T& a):
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

    template<typename T>
    GenericMatrix<T>::~GenericMatrix() {
        if (data_ != nullptr) {
            delete[] *data_;
            delete[] data_;
        }
    }

    template <typename T>
    GenericMatrix<T>::GenericMatrix(const GenericMatrix<T>& that):
            n_(that.n_), m_(that.m_), data_(that.n_ > 0 ? new T*[that.n_] : nullptr) {
        allocate(n_, m_);

        if (data_ != nullptr) {
            std::copy(that.data_[0], that.data_[0] + that.size(), data_[0]);
        }
    }

    template<typename T>
    GenericMatrix<T>::GenericMatrix(GenericMatrix&& that) noexcept:
            n_(that.n_), m_(that.m_), data_(that.data_) {
        that.data_ = nullptr;
        that.n_ = that.m_ = 0;
    }

    template<typename T>
    GenericMatrix<T>& GenericMatrix<T>::operator=(const GenericMatrix<T>& that) {
        if (data_ != nullptr) {
            delete[] *data_;
            delete[] data_;
        }

        n_ = that.n_;
        m_ = that.m_;
        data_ = n_ > 0 ? new T*[n_] : nullptr;

        allocate(n_, m_);

        if (data_ != nullptr) {
            std::copy(that.data_[0], that.data_[0] + that.size(), data_[0]);
        }

        return *this;
    }

    template<typename T>
    GenericMatrix<T>& GenericMatrix<T>::operator=(GenericMatrix&& that) noexcept {
        if (data_ != nullptr) {
            delete[] *data_;
            delete data_;
        }

        n_ = that.n_;
        m_ = that.m_;
        data_ = that.data_;

        that.data_ = nullptr;
        that.n_ = that.m_ = 0;

        return *this;
    }

    template<typename T>
    bool GenericMatrix<T>::operator==(const GenericMatrix<T>& that) const {
        if (n_ != that.n_ || m_ != that.m_)
            return false;

        return std::equal(data_[0], data_[0] + size(), that.data_[0]);
    }

    template<typename T>
    void GenericMatrix<T>::resize(std::size_t n, std::size_t m) {
        *this = GenericMatrix(n, m);
    }

    template<typename T>
    void GenericMatrix<T>::assign(std::size_t n, std::size_t m, const T& a) {
        *this = GenericMatrix(n, m, a);
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
