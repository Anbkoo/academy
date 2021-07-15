#pragma once
#include <iostream>  
#include <string>  

struct count_pointer
    {
    size_t count_shared = 1, count_weak = 0;
    };


template <class T>
class shared_pointer
    {
    public:
        shared_pointer() : ptr(nullptr), count_ptr(nullptr) {};
        explicit shared_pointer(T* t) :ptr(t), count_ptr(new count_pointer()){};

        void check_pointer_to_reset()
            {
            if (count_ptr)
                {
                --count_ptr->count_shared;
                if (!count_ptr->count_shared)
                    {
                    delete ptr;
                    ptr = nullptr;
                    if (!count_ptr->count_weak)
                        {
                        delete count_ptr;
                        count_ptr = nullptr;
                        }
                    }
                }
            }

        ~shared_pointer()
            {
            check_pointer_to_reset();
            };

        // copy 
        shared_pointer(const shared_pointer& tmp) 
            : ptr(tmp.ptr), count_ptr(tmp.count_ptr)
            {
            ++count_ptr->count_shared;
            }
        shared_pointer<T>& operator= (const shared_pointer& tmp)
            {
            check_pointer_to_reset();

            ptr = tmp.ptr;
            count_ptr = tmp.count_ptr;
            ++count_ptr->count_shared;
            return *this;
            }

        // move 
        shared_pointer(shared_pointer&& tmp) noexcept
            : ptr(std::move(tmp.ptr)), count_ptr(std::move(tmp.count_ptr))
            {
            tmp.ptr = nullptr;
            tmp.count_ptr = nullptr;
            }
        shared_pointer<T>& operator= (shared_pointer&& tmp)
            {
            reset(ptr);

            this->ptr = tmp.ptr;
            this->count_ptr = tmp.count_ptr;
            tmp.ptr = nullptr;
            tmp.count_ptr = nullptr;
            return *this;
            }

        void reset(T* t, count_pointer* count_ptr) noexcept
            {
            delete t;
            delete count_ptr;
            t = nullptr;
            count_ptr = nullptr;
            }

        void reset() noexcept
            {
            check_pointer_to_reset();
            ptr = nullptr;
            count_ptr = nullptr;
            }

        T* operator->() const noexcept
            {
            return ptr;
            }
        T& operator*() const noexcept
            {
            return *ptr;
            }

        T* ptr;
        count_pointer* count_ptr;
    };

template<class T, class... Args >
shared_pointer<T> make_shared(Args&&... args)
    {
    return shared_pointer<T>(new T(std::forward<Args>(args)...));
    }