#include <iostream>  
#include <string>  

class count_shared
    {
    private:
        size_t count;
    public:
        count_shared() :count(0) {};
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
        shared_point() : ptr(nullptr), count_ptr(nullptr) 
            {
            count_ptr = new count_shared();
            count_ptr->add_count();
            };
        explicit shared_point(T& t) :ptr(t), count_ptr(nullptr)
            {
            count_ptr = new count_shared();
            count_ptr->add_count();
            };

        ~shared_point()
            {
            count_ptr->subtract_count();
            if (!count_ptr->get_count())
                {
                reset(ptr);
                } 
            };

        // copy 
        shared_point(const shared_point& tmp) : ptr(tmp.ptr), count_ptr(tmp.count_ptr)
            {
            count_ptr->add_count();
            }


        shared_point& operator= (const shared_point& tmp)
            {
            ptr = tmp.ptr;
            count_ptr = tmp.count_ptr;
            count_ptr->add_count();
            return *this;
            }

        // move 
        shared_point(shared_point&& tmp) noexcept
            : ptr(std::move(tmp.ptr))
            {
            tmp.ptr = nullptr;
            };

        shared_point& operator= (shared_point&& tmp)
            {
                reset(ptr);

                this->ptr = tmp.ptr;
                this->count_ptr = tmp.count_ptr;
                tmp.ptr = tmp.count_ptr = nullptr;
                return this;
            }

        void reset(T* t) noexcept
            {
                delete t;
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
        T* ptr = nullptr; 
        count_shared* count_ptr = nullptr;
    };

class A 
    {
    private:
        int data;
    public:
    void set_data(int _data)
        {
        data = _data;
        }

    int get_data()
        {
        return data;
        }
    
        
    };

int main() 
{
    shared_point<A> _temp1;
    _temp1->set_data(5);
    std::cout << _temp1->get_data() << std::endl;
    const shared_point<A> _temp = std::move(_temp1);

    std::cout << _temp->get_data() << std::endl;
    std::cout << _temp1->get_data() << std::endl;
    shared_point<A> _temp2 = _temp;

    std::cout << _temp->get_data() << std::endl;
    std::cout << _temp2->get_data() << std::endl;

    
    //_temp->data;

    std::cin.get();
    return 0;
}
