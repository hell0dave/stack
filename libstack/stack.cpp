#include <iostream>
#include "stack.h"


bool stack::push (const int32_t new_element)
{
    if (this->top == 0) {
        this->capacity = 1;
        this->data = std::make_unique<int32_t[]>(this->capacity);
    }
    else {
        if (this->top == this->capacity) {
            this->capacity*=2;
            std::unique_ptr<int32_t[]> t {std::make_unique<int32_t[]>(this->capacity)};
            for (uint64_t i = 0; i < this->top; i++) {
                t[i] = this->data[i];
            }
            this->data = std::move(t);
        }
    }
        
    this->data[this->top++] = new_element;
    return true;
}


int32_t stack::pop()
{
    if (this->top == 0)
        throw std::runtime_error("Nothing to pop");
    
    if (this->top == this->capacity/2) {
        this->capacity/=2;
        std::unique_ptr<int32_t[]> t {std::make_unique<int32_t[]>(this->capacity)};
        for (uint64_t i = 0; i < this->top; i++) {
            t[i] = this->data[i];
        }
        this->data = std::move(t);
    }
    this->top--;
    
    return this->data[this->top];
}

