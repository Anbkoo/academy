#include <iostream>  
#include <string>  

template <class T>
class unq_point
    {
    public:
        unq_point() : ptr(nullptr) {};
        explicit unq_point(T& t) :ptr(t) {};

        ~unq_point() 
            {
            if (ptr)
                delete ptr;
            };

        // copy 
        unq_point (const unq_point& tmp) = delete;
        unq_point& operator= (const unq_point& tmp) = delete;

        // move 
        unq_point(unq_point&& tmp) noexcept 
            : ptr(std::move(tmp.ptr))
            {
            tmp.ptr = nullptr;
            };

        unq_point& operator= (unq_point&& tmp)
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
                return &ptr;
            }
    private:
        T* ptr = nullptr;
    };

class A 
    {
    public:
        int data;
    };

int main() 
{
    unq_point<A> _temp1;
    unq_point<A> _temp = std::move(_temp1);
    _temp.reset(nullptr);
    _temp->data;

    std::cin.get();
    return 0;
}