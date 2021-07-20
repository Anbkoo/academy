#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "deque.h"

class CustomAllocator
    {
    public:
        CustomAllocator(const size_t _total_size);
        ~CustomAllocator();

        void* allocate(const size_t n);
        void deallocate(void* temp);
        void printList();

        std::size_t get_total_block_size();
    private:
        char* total_block = nullptr;
        char* total_block_end = nullptr;
        list* list_of_node = nullptr;
    };

CustomAllocator::CustomAllocator(const size_t _total_size)
    {
    total_block = new char(_total_size + 1);
    total_block_end = total_block + _total_size + 1;

    list_of_node = new list();
    list_of_node->set_memmory(total_block, _total_size);
    }

CustomAllocator::~CustomAllocator()
    {
    if (total_block)
        delete (total_block);

    delete list_of_node;
    }

std::size_t CustomAllocator::get_total_block_size()
    {
    return total_block_end - total_block;
    }

void* CustomAllocator::allocate(const size_t n)
    {
    if (!list_of_node->get_head())
        {
        return list_of_node->insert_to_begin(n);
        }
    else
        {
        return list_of_node->insert_node(n);
        }
    }

void CustomAllocator::deallocate(void* temp)
    {
    if (!temp || !list_of_node->get_head())
        return;
    list_of_node->find_to_delete(temp);
    }

void CustomAllocator::printList()
    {
    list_of_node->printList();
    }