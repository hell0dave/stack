#ifndef Header_h
#define Header_h

#define STACK_SIZE 100


class stack {
    
private:
    
    std::unique_ptr <int32_t[]> data;
    uint64_t top = 0;
    uint64_t capacity = 0;
    
public:
    
    int32_t pop();
    
    bool push (const int32_t new_element);
    
    inline bool is_empty()
    {
    return (top == 0) ? true : false;
    }
};

#endif /* Header_h */
