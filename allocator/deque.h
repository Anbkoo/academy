#pragma once

struct Block
    {
    char* start = nullptr;
    std::size_t size = 0;
    };

struct Node {
    Block block;
    Node* prev = nullptr;
    Node* next = nullptr;
    };

class list {
public:
    std::size_t size_of_list = 0;

    list() = default;
    ~list();
    Node* get_element_by_address(void* _temp);
    Node* get_head();
    Node* get_tail();
    void set_memmory(char* total_block, const std::size_t n);

    std::size_t size();
    void* insert_to_begin(const std::size_t n);
    void* insert_node(const std::size_t n);
    void* insert_to_end(const std::size_t n);

    void find_to_delete(void* _temp);
    void delete_from_begin();
    void delete_node(void* _temp);
    void delete_from_end();

    void printList();
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t total_size = 0;
    char* curr_memmory = nullptr;    
    };

list::~list()
    {
    while (head)
        {
        tail = head->next;
        delete head;
        head = tail;
        }
    }

Node* list::get_head()
    {
    return head;
    }

Node* list::get_tail()
    {
    return tail;
    }

void list::set_memmory(char* total_block, const std::size_t n)
    {
    curr_memmory = total_block;
    total_size = n;
    }

std::size_t list::size()
    {
    return size_of_list;
    }

Node* list::get_element_by_address(void* _temp) {
    Node* temp = head;

    while (temp) {
        if (temp->block.start == _temp)
            break;
        temp = temp->next;
        }

    return temp;
    }

void* list::insert_to_begin(const size_t n)
    {
    Node* temp = new Node();
    if (!head)
        {
        temp->block = Block{ curr_memmory, n };
        temp->next = temp->prev = nullptr;
        head = tail = temp;
        curr_memmory = temp->block.start + n;
        }

    size_of_list++;
    return temp->block.start;
    }

void* list::insert_node(const size_t n)
    {
    Node* temp = new Node();
    Node* _temp = head;
    while (_temp->next)
        {
        if ((_temp->next->block.start - _temp->block.start - _temp->block.size) >= n)
            {
            temp->next = _temp->next;
            temp->prev = _temp;
            _temp->next->prev = temp;

            curr_memmory = _temp->block.start + _temp->block.size;
            temp->block = Block{ curr_memmory, n };
            _temp->next = temp;
            
            
            size_of_list++;
            return temp->block.start;
            }
        _temp = _temp->next;
        }

    delete temp;
    temp = nullptr;
    return insert_to_end(n);
    }

void* list::insert_to_end(const size_t n)
    {

    if ((curr_memmory - head->block.start + n) > total_size)
        {
        std::cout << "can not allocate memmory of " << n << std::endl;
        return {};
        }

    Node* temp = new Node();
    temp->block = Block{ curr_memmory, n };
    temp->prev = tail;
    tail->next = temp;
    temp->next = nullptr;
    tail = temp;
    curr_memmory = temp->block.start + n;
    size_of_list++;
    return temp->block.start;
    }

void list::printList()
    {
    Node* temp = head;
    std::cout << "print list" << std::endl;
    if (!temp)
        {
        std::cout << "list is empty" << std::endl;
        return;
        }

    while (temp)
        {
        std::cout << " " << temp->block.size << std::endl;
        temp = temp->next;
        }
    }

void list::find_to_delete(void* _temp)
    {
    if (head->block.start == _temp)
        {
        delete_from_begin();
        }

    else if (tail->block.start == _temp)
        {
        delete_from_end();
        }
    else
        {
        delete_node(_temp);
        }
    }

void list::delete_from_begin()
    {
    if (!head)
        return; 

    if (head != tail)
        {
        head->next->prev = nullptr;
        head = head->next;
        }
    else
        {
        head = tail = nullptr;
        }
    size_of_list--;
    }

void list::delete_node(void* _temp)
    {
    if (head == _temp || tail == _temp)
        return;

    Node* temp = get_element_by_address(_temp);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    delete temp;
    temp = nullptr;
    size_of_list--;
    }

void list::delete_from_end()
    {
    if (tail == head)
        return;

    tail = tail->prev;
    tail->next = nullptr;
    size_of_list--;
    }