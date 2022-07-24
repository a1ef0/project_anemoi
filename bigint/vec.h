#ifndef VEC_H
#define VEC_H

#include <cstddef>
#include <cstdlib>

namespace anemoi {

typedef unsigned int uint;

/**
 * @brief The simple vec class which provides basic wrapper around T[].
 */
template <class T>
class vec {
public:
    uint size;

    vec(){
        size = DEFAULT_SIZE;
        //_container = new T[DEFAULT_SIZE];
        _container = (T*)calloc(DEFAULT_SIZE, sizeof(T));
    }

    ~vec(){
        size = 0;
        delete[] _container;
    }

    vec(uint size) {
        this->size = size;
        //_container = new T[size];
        _container = (T*)calloc(size, sizeof(T));
    }

    vec(const vec& src){
        size = src.size;
        _container = new T[size];
        for (size_t i = 0; i < size; ++i){
            _container[i] = src._container[i];
        }
    }

    vec(vec&& src){
        size = src.size;
        _container = src._container;
        src._container = nullptr;
    }

    T& operator [] (uint idx){
        return (*this)._container[idx];
    }

    T operator [] (uint idx) const{
        return (*this)._container[idx];
    }

    vec& operator =(const vec& src){
        size = src.size;
        _container = new T[size];
        for (size_t i = 0; i < size; ++i){
            _container[i] = src._container[i];
        }
        return *this;
    }

    vec& operator =(vec&& src){
        size = src.size;
        _container = src._container;
        src._container = nullptr;
        return *this;
    }
private:
    static const uint DEFAULT_SIZE = 16;
    T* _container;
};

}
#endif // VEC_H
