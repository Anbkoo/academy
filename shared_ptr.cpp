#include <iostream>  
#include <string>  

class count_shared
    {
    private:
        size_t count = 0;
    public:
        count_shared() : count(0) {};
        void add_count()
            {
            ++count;
            }

        void subtract_count()
            {
            --count;
            }

        size_t get_count()
            {
            return count;
            }
    };

template <class T>
class shared_point
    {
    public:
        shared_point() : ptr(nullptr), count_ptr(0) {};
        explicit shared_point(T* t) :ptr(t), count_ptr(0)
            {
            count_ptr = new count_shared();
            count_ptr->add_count();
            };

        ~shared_point()
            {
            if (ptr)
                {
                count_ptr->subtract_count();
                if (!count_ptr->get_count())
                    {
                    reset(ptr, count_ptr);
                    }
                }
            };

        // copy 
        shared_point(const shared_point& tmp) : ptr(tmp.ptr), count_ptr(tmp.count_ptr)
            {
            count_ptr->add_count();
            }


        shared_point<T>& operator= (const shared_point& tmp)
            {
            ptr = tmp.ptr;
            count_ptr = tmp.count_ptr;
            count_ptr->add_count();
            return *this;
            }

        // move 
        shared_point(shared_point&& tmp) noexcept
            : ptr(std::move(tmp.ptr)), count_ptr(std::move(tmp.count_ptr))
            {
            tmp.ptr = nullptr;
            tmp.count_ptr = nullptr;
            }

        shared_point<T>& operator= (shared_point&& tmp)
            {
            reset(ptr);

            this->ptr = tmp.ptr;
            this->count_ptr = tmp.count_ptr;
            tmp.ptr = tmp.count_ptr = nullptr;
            return this;
            }

        void reset(T* t, count_shared* count_ptr) noexcept
            {
            delete t;
            delete count_ptr;
            }

        T* operator->() const noexcept
            {
            return ptr;
            }

        T& operator*() const noexcept
            {
            return *ptr;
            }
    private:
        T* ptr;
        count_shared* count_ptr;
    };

class A
    {
    private:
        int data = 0;
    public:
        explicit A(int _data) : data(_data) {};

        void set_data(const int _data)
            {
            data = _data;
            }

        const int get_data()
            {
            return data;
            }


    };

int main()
    {
    shared_point<A> _temp1(new A(5));
    std::cout << _temp1->get_data() << std::endl;
    const shared_point<A> _temp = std::move(_temp1);

    std::cout << _temp->get_data() << std::endl;
    shared_point<A> _temp2;
    _temp2 = _temp;

    std::cout << _temp->get_data() << std::endl;
    std::cout << _temp2->get_data() << std::endl;

    return 0;
    }