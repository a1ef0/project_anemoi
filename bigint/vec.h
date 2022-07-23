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
        _container = new T[DEFAULT_SIZE];
        _container = (T*)(malloc(DEFAULT_SIZE * sizeof(T)));
    }

    ~vec(){
        size = 0;
        delete[] _container;
    }

    vec(uint size) {
        this->size = size;
        _container = new T[size];
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
        //*this = vec(src);
        this->size = src.size;
        this->_container = new T[size];
        //vec *ptr = (vec *)malloc(sizeof(vec *) + DEFAULT_SIZE * sizeof(int));
        for (size_t i = 0; i < size; ++i){
            _container[i] = src._container[i];
        }
        return *this;
    }
private:
    static const uint DEFAULT_SIZE = 16;
    T* _container;
};

}
#endif // VEC_H
