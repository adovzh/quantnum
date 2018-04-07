//
// Created by Alexander Dovzhikov on 4/4/18.
//

#ifndef QUANTNUM_VECTOR_H
#define QUANTNUM_VECTOR_H

#include <cstddef>

namespace quantnum {

    template <typename T>
    class GenericVector {
    public:
        explicit GenericVector(std::size_t n = 0);
        GenericVector(std::size_t n, const T& a);
        GenericVector(std::size_t n, const T* a);
        ~GenericVector() { if (data_ != nullptr) delete[] data_; }

        GenericVector(const GenericVector& that);
        GenericVector(GenericVector&& that) noexcept;
        GenericVector& operator=(const GenericVector& that);
        GenericVector& operator=(GenericVector&& that) noexcept;
        bool operator==(const GenericVector& that) const;
        bool operator!=(const GenericVector& that) const { return !(*this == that); }

        const T& operator[](std::size_t index) const { return data_[index]; }
        T& operator[](std::size_t index) { return data_[index]; }

        std::size_t size() const { return size_; }
    private:
        void allocate() { data_ = size_ > 0 ? new T[size_] : nullptr; }

        T* data_;
        std::size_t size_;
    };

    template <typename T>
    inline GenericVector<T>::GenericVector(std::size_t n): size_(n) {
        allocate();
    }

    template <typename T>
    inline GenericVector<T>::GenericVector(std::size_t n, const T& a): size_(n) {
        allocate();
        std::fill(data_, data_ + n, a);
    }

    template <typename T>
    inline GenericVector<T>::GenericVector(size_t n, const T* a): size_(n) {
        allocate();
        std::copy(a, a + n, data_);
    }

    template<typename T>
    inline GenericVector<T>::GenericVector(const GenericVector& that): size_(that.size_) {
        allocate();
        std::copy(that.data_, that.data_ + size_, data_);
    }

    template<typename T>
    inline GenericVector<T>::GenericVector(GenericVector&& that) noexcept : size_(that.size_), data_(that.data_) {
        that.data_ = nullptr;
        that.size_ = 0;
    }

    template<typename T>
    GenericVector<T>& GenericVector<T>::operator=(const GenericVector& that) {
        if (this != &that) {
            if (data_ != nullptr)
                delete[] data_;

            size_ = that.size_;
            allocate();
            std::copy(that.data_, that.data_ + size_, data_);
        }

        return *this;
    }

    template<typename T>
    GenericVector<T>& GenericVector<T>::operator=(GenericVector<T>&& that) noexcept {
        if (this != &that) {
            if (data_ != nullptr)
                delete[] data_;

            size_ = that.size_;
            data_ = that.data_;

            that.size_ = 0;
            that.data_ = nullptr;
        }

        return *this;
    }

    template<typename T>
    bool GenericVector<T>::operator==(const GenericVector<T>& that) const {
        if (size_ != that.size_) return false;

        for (std::size_t i = 0; i < size_; i++)
            if (data_[i] != that.data_[i])
                return false;

        return true;
    }

    typedef GenericVector<double> Vector;
}


#endif //QUANTNUM_VECTOR_H
