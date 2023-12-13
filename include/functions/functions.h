#pragma once

#include <iostream>

#include <cmath>

#include <complex>

#include <stdexcept>

using namespace std;

namespace polynom {

    template<typename T>

    class Polynomial {

    private:
        T* _data;
        size_t _size;
        inline static const double EPSILION = 0.001;

    public:
        Polynomial(size_t size) : _size(size), _data(new T[size]()) {}

        Polynomial(T* data, size_t size) : _data(new T[size]), _size(size) {
            for (size_t i = 0; i < _size; i++) {
                _data[i] = data[i];
            }
        }
        
        ~Polynomial() {
            delete[] _data;
            _data = nullptr;
            _size = 0;
        }

        Polynomial(const Polynomial<T>& a) : _data(new T[a._size]), _size(a._size) {
            for (size_t i = 0; i < _size; i++) {
                _data[i] = a[i];
            }
        }

        size_t size() const {
            return _size;
        }

        size_t get_size() const {
            return _size;
        }

        T* get_data() const {
            return _data;
        }

        T operator[](size_t index) const {
            if (_size <= index) {
                return 0;
            }
            return _data[index];
        }

        void expand(size_t size) {
            if (size < _size) {
                throw std::out_of_range("this power is alredy exsists.");
            }
            auto temp = (new T[size]());
            for (size_t i = 0; i < _size; i++) {
                temp[i] = _data[i];
            }
            delete[] _data;
            _data = temp;
            _size = size;
        }

        void set(T data, size_t index) {
            if (index > _size) {
                expand(index + 1);
            }
            _data[index] = data;
        }

        void swap(Polynomial<T>& a) {
            std::swap(_data, a._data);
            std::swap(_size, a._size);
        }

        void shrink_to_fit() {
            T zero = T(0);
            for (size_t i = _size - 1; i > 0; i--) {
                if (_data[i] != zero) {
                    i++;
                    auto temp = (new T[i]());
                    for (size_t j = 0; j < i; j++) {
                        temp[j] = _data[j];
                    }
                    delete[] _data;
                    _data = temp;
                    _size = i;
                    break;
                }
            }
        }
        
        Polynomial<T>& operator=(Polynomial<T> a) {
            delete[] _data;
            _size = a._size;
            _data = (new T[_size]());
            for (size_t i = 0; i < _size; i++) {
                _data[i] = a[i];
            }
            return *this;
        }

        Polynomial<T>& operator+= (const Polynomial<T>& a) {
            if (a.size() > _size) {

                expand(a.size());
            }
            for (size_t i = 0; i < a._size; i++) {
                _data[i] += a[i];
            }
            return *this;
        }

        Polynomial<T>& operator-= (const Polynomial<T>& a) {
            if (a.size() > _size) {
                expand(a.size());
            }
            for (size_t i = 0; i < a._size; i++) {
                _data[i] -= a[i];
            }
            return *this;
        }

        Polynomial<T> operator- (Polynomial<T> a) const {
            return a -= *this;
        }

        Polynomial<T> operator+ (Polynomial<T> a)  const {
            return a += *this;
        }

        Polynomial<T> operator*(const T& a) {
            Polynomial<T> copy = Polynomial<T>(this->_size);
            copy._size = this->_size;
            for (size_t i = 0; i < _size; i++) {
                copy._data[i] = _data[i];
                copy._data[i] *= a;

            }
            return copy;
        }

        bool operator== (Polynomial<T> a) const {
            a.shrink_to_fit();
            Polynomial<T> copy(*this);
            copy.shrink_to_fit();
            if (copy._size != a._size) { return false; }
            for (size_t i = 0; i < a._size; i++) {
                if (std::abs(_data[i] - a._data[i]) > EPSILION) {
                    return false;
                }
            }
            return true;
        }

        bool operator!= (const Polynomial<T>& a) const {
            return !(a == *this);
        }

        friend Polynomial<T> operator* (const T& a, const Polynomial<T>& pol) {
            Polynomial<T> res = pol;
            res = res * a;
            return res;
        }
        T calculation_Polynomial_x(const T& x) {
            T sum = 0;
            for (size_t i = 0; i < _size; i++) {
                sum += _data[i] * pow(x, i);
            }
            return sum;
        }
    };

    template<typename T>

    Polynomial<T> differentiate(Polynomial<T> polynomial) {
        Polynomial<T> temp_polyn(polynomial.get_size()-1);
        for (int i = 1; i < polynomial.get_size(); i++) {
            temp_polyn.set(i * polynomial[i],i-1);
        }
        return temp_polyn;
    }

    template<typename T>
    std::ostream& operator << (std::ostream& stream, const Polynomial<T>& a) {
        for (size_t i = 0; i < a.size(); ++i) {
            if (i == 0) {
                stream << a[i];
            }
            else if (i == 1) {
                stream << " + " << a[i] << "*x";
            }
            else {
                stream << " + " << a[i] << "*x^" << i;
            }
        }
        return stream;
    }
};