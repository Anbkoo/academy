#pragma once
#include <iostream>  

template <class T>
class unique_pointer
    {
    public:
        unique_pointer() : ptr(nullptr) {};
        explicit unique_pointer(T* t) :ptr(t) {};

        ~unique_pointer()
            {
            if (ptr)
                delete ptr;
            };

        // copy 
        unique_pointer(const unique_pointer& tmp) = delete;
        unique_pointer& operator= (const unique_pointer& tmp) = delete;

        // move 
        unique_pointer(unique_pointer&& tmp) noexcept
            : ptr(std::move(tmp.ptr))
            {
            tmp.ptr = nullptr;
            };

        unique_pointer& operator= (unique_pointer&& tmp)
            {
            if (ptr)
                delete ptr;

            this->ptr = tmp.ptr;
            tmp.ptr = nullptr;
            return this;
            }

        T* release() noexcept
            {
            T* result = nullptr;
            std::swap(result, ptr);
            return result;
            }

        void reset(T* t) noexcept
            {
            delete t;
            }

        T* operator->() const noexcept
            {
            return ptr;
            }
    private:
        T* ptr = nullptr;
    };

template<typename T, typename... Args>
unique_pointer<T> make_unique(Args&&... args)
    {
    return unique_pointer<T>(new T(std::forward<Args>(args)...));
    }
