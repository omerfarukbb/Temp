#ifndef ORTALAMA_HPP
#define ORTALAMA_HPP

#include <iostream>
#include <queue>

/**
 * @brief A class for calculating the rolling average of a sequence of values.
 *
 * @details This class provides a templated mechanism to calculate the rolling average of a sequence of values.
 */
template <class T>
class Ortalama {
    std::queue<T> _list;
    const size_t _N;
    T _ort;

public:
    Ortalama(size_t N);
    const T& ortalama = _ort;

    void add(T x);
    void reset();
};

// template class needs an explicit instantation of the template
// when a source file is used
// instead, source code is moved to the header

#include <cassert>

template <class T>
Ortalama<T>::Ortalama(size_t N)
    : _N(N)
    , _ort(0)
{
    assert(N > 0);
}

template <class T>
void Ortalama<T>::add(T x)
{
    _ort = (_ort * _list.size() + x) / (_list.size() + 1);
    _list.push(x);

    if (_list.size() > _N) {
        _ort = (_ort * _list.size() - _list.front()) / (_list.size() - 1);
        _list.pop();
    }
}

template <class T>
void Ortalama<T>::reset()
{
    _list = std::queue<T>();
    _ort = 0;
}

#endif
