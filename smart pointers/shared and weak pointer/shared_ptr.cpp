#include "shared_ptr.h" 

void count_shared::add_count()
    {
    ++count;
    }

void count_shared::subtract_count()
    {
    --count;
    }

size_t count_shared::get_count()
    {
    return count;
    }


template <class T>
shared_point<T>& shared_point<T>::operator= (shared_point<T>&& tmp)
    {
    reset(ptr);

    this->ptr = tmp.ptr;
    this->count_ptr = tmp.count_ptr;
    tmp.ptr = tmp.count_ptr = nullptr;
    return this;
    }

template <class T>
void shared_point<T>::reset(T* t, count_shared* count_ptr) noexcept
    {
    delete t;
    delete count_ptr;
    }

template <class T>
T* shared_point<T>::operator->() const noexcept
    {
    return ptr;
    }

template <class T>
T& shared_point<T>::operator*() const noexcept
    {
    return *ptr;
    }