#pragma once
#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;
    };

template<typename T>
class list {
public:
    std::size_t size_of_list = 0;

    list() = default;
    ~list();
    explicit list(bool _view) : view(_view) {};
    auto get_element_by_index(std::size_t index);

    std::size_t size();
    void insert_to_begin(T value);
    void insert_node(std::size_t position, T value);
    void insert_to_end(T value);

    void delete_from_begin();
    void delete_node(std::size_t position);
    void delete_from_end();

    void printList();
private:
    bool view;
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    };

template<typename T>
list<T>::~list()
    {
    while (head)
        {
        tail = head->next;
        delete head;
        head = tail;
        }
    }

template<typename T>
std::size_t list<T>::size()
    {
    return size_of_list;
    }

template<typename T>
auto list<T>::get_element_by_index(std::size_t index) {
    Node<T>* temp = head;
    std::size_t i = 0;

    while (temp && i < index) {
        temp = temp->next;
        i++;
        }

    return temp;
    }

template<typename T>
void list<T>::insert_to_begin(T value)
    {
    Node<T>* temp = new Node<T>();
    temp->data = value;
    if (!head)
        {
        temp->next = temp->prev = nullptr;
        head = tail = temp;
        }
    else
        {
        temp->next = head;
        temp->prev = nullptr;
        head->prev = temp;
        head = temp;
        }
    size_of_list++;
    }

template<typename T>
void list<T>::insert_node(std::size_t position, T value)
    {
    if (position < 0 || position > size())
        {
        return;
        }
    else if (position == 0)
        {
        insert_to_begin(value);
        }
    else if (position == size())
        {
        insert_to_end(value);
        }
    else
        {
        Node* _temp = get_element_by_index(position);
        Node* temp = new Node();
        _temp->next->prev = temp;
        temp->data = value;
        _temp->next = temp;
        size_of_list++;
        }
    }

template<typename T>
void list<T>::insert_to_end(T value)
    {
    Node<T>* temp = new Node<T>();
    temp->data = value;
    temp->prev = tail;
    tail->next = temp;
    temp->next = nullptr;
    tail = temp;
    size_of_list++;
    }

template<typename T>
void list<T>::printList()
    {
    Node<T>* temp = head;
    std::cout << "print list" << std::endl;
    if (!temp)
        {
        std::cout << "list is empty" << std::endl;
        return;
        }

    while (temp)
        {
        std::cout << " " << temp->data << std::endl;
        temp = temp->next;
        }
    }

template<typename T>
void list<T>::delete_from_begin()
    {
    if (!head)
        return; 

    head = head->next;
    if (head)
        head->prev = nullptr;
    size_of_list--;
    }

template<typename T>
void list<T>::delete_node(std::size_t position)
    {
    if (position < 0 || position > size() - 1)
        return;

    Node<T>* _temp = get_element_by_index(position);
    if (head == _temp)
        {
        delete_from_begin();
        }
    else if (tail == _temp)
        {
        delete_from_end();
        }
    else {
        _temp->prev->next = _temp->next;
        _temp->next->prev = _temp->prev;
        size_of_list--;
        }
    
    }

template<typename T>
void list<T>::delete_from_end()
    {
    if (tail == head)
        return;

    tail = tail->prev;
    tail->next = nullptr;
    size_of_list--;
    }