#pragma once
#include "shared_pointer.h" 

template <typename T>
class weak_pointer {
public:
    weak_pointer() : ptr(nullptr), weak_count(nullptr) {};

    ~weak_pointer()
        {
        check_pointer_to_reset();
        }

    void check_pointer_to_reset()
        {
        if (weak_count)
            {
            --weak_count->count_shared;
            if (!weak_count->count_shared)
                {
                delete ptr;
                ptr = nullptr;
                if (!weak_count->count_weak)
                    {
                    delete weak_count;
                    weak_count = nullptr;
                    }
                }
            }
        }

    void reset() noexcept
        {
        check_pointer_to_reset();
        ptr = nullptr;
        weak_count = nullptr;
        }

    // copy
    weak_pointer(const weak_pointer& wp) noexcept
        : ptr(wp.ptr), weak_count(wp.weak_count) {
        if (weak_count)
            ++weak_count->weak_count;
        }

    weak_pointer(const shared_pointer<T>& sp) noexcept
        : ptr(sp.ptr), weak_count(sp.count_ptr) {
        if (weak_count)
            ++weak_count->count_weak;
        }

    weak_pointer<T>& operator=(const weak_pointer& tmp) noexcept
        {
        check_pointer_to_reset();

        ptr = tmp.ptr;
        weak_count = tmp.weak_count;
        ++weak_count->count_weak;
        return *this;
        }

    //move
    weak_pointer(weak_pointer&& tmp) noexcept
        : ptr(std::move(tmp.ptr)), weak_count(std::move(tmp.weak_count))
        {
        reset(tmp);
        }

    weak_pointer<T>& operator= (weak_pointer&& tmp)
        {
        reset(ptr);

        this->ptr = tmp.ptr;
        this->weak_count = tmp.weak_count;
        tmp.ptr = nullptr;
        tmp.weak_count = nullptr;
        return *this;
        }

    shared_pointer<T> lock() const {
        return expired() ? shared_pointer<T>(nullptr) : shared_pointer<T>(*this);
        }

    bool expired() const noexcept {
        return ((!weak_count) || (weak_count->count_shared)) <= 0;
        }


private:
    T* ptr;
    count_pointer* weak_count = nullptr;

    template<class Y> friend class shared_pointer;
    };