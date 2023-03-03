
#include <iostream>
#include <vector>
#include <algorithm>
#include <string_view>
#include <string>
#include "stack.h"
#include <random>
#include <memory>


std::string get_order_of_calls(std::vector<uint8_t> functions)
{
    std::string result{};
    uint8_t i {0};
    for (auto &num: functions) {
        switch (num) {
            case 1:
                result += "push";
                break;
            case 2:
                result += "pop";
                break;
            case 3:
                result += "is_empty";
        }
        i++;
        
        if (i != 3)
            result += ", ";
    }
        
    return result;
}

int main()
{
    stack s1;
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution dist (0, 100);

    std::vector<uint32_t> stack_states {0, 1, STACK_SIZE/2, STACK_SIZE-1, STACK_SIZE};
    int32_t push_value {dist(generator)};

    bool ref_push_result {false};
    int32_t ref_pop_value {0};
    bool ref_pop_status {false};
    bool ref_is_full_result {false};
    bool ref_is_empty_result {false};


    int32_t ref_pop_value_before_push {0};
    bool ref_is_full_before_pop {false};
    bool ref_is_full_after_push {false};
    bool ref_is_full_after_pop {false};
    bool ref_is_empty_result_before_pop {false};


    // A for loop goes through the states
    for (auto &state: stack_states) {

        std::vector<uint8_t> functions { 1, 2, 3 };
        int32_t rand_num = dist(generator);
        // stack initialization (reset)
        switch (state) {
            case 0:
                break;
            case 1:
                break;
            case STACK_SIZE/2:
                // добавляется 49 элементов
                for (int32_t i = 0; i < STACK_SIZE/2-1; ++i)
                    s1.push(i + 1);
                break;
            case STACK_SIZE-1:
                // добаволяется SS-1 элементов к SS/2-1 элементов
                for (int32_t i = 0; i < STACK_SIZE/2-1; ++i)
                    s1.push(i + STACK_SIZE/2 + 1);
                break;
            case STACK_SIZE:
                s1.push(STACK_SIZE-1);
                break;
            default:
                std::cout << "Stack size unknown," << " stack_size = " << static_cast<int>(state) << std::endl;
                break;
        }

        do  {
            // Initialization of tokens before each method sequence is called
            switch (state) {
                case 0:
                    ref_pop_value = 0;
                    ref_pop_value_before_push = 0;
                    ref_push_result = true;
                    ref_is_empty_result_before_pop = true;
                    ref_is_empty_result = true;
                    ref_pop_status = false;
                    ref_is_full_after_push = false;
                    ref_is_full_before_pop = false;
                    ref_is_full_after_pop = false;
                    ref_is_full_result = false;
                    break;
                case 1:
                    s1.push(rand_num);
                    ref_push_result = true;
                    ref_pop_value = push_value;
                    ref_pop_value_before_push = rand_num;
                    ref_is_empty_result_before_pop = true;
                    ref_pop_status = true;
                    ref_is_empty_result = false;
                    ref_is_full_after_push = false;
                    ref_is_full_before_pop = false;
                    ref_is_full_after_pop = false;
                    ref_is_full_result = false;
                    break;
                case STACK_SIZE/2:
                    s1.push(STACK_SIZE/2);
                    ref_push_result = true;
                    ref_pop_value = push_value;
                    ref_pop_value_before_push = STACK_SIZE/2;
                    ref_pop_status = true;
                    ref_is_empty_result = false;
                    ref_is_empty_result_before_pop = false;
                    ref_is_full_after_push = false;
                    ref_is_full_before_pop = false;
                    ref_is_full_after_pop = false;
                    ref_is_full_result = false;
                    break;
                case STACK_SIZE-1:
                    s1.push(STACK_SIZE-1);
                    ref_push_result = true;
                    ref_pop_value = push_value;
                    ref_pop_value_before_push = STACK_SIZE-1;
                    ref_is_full_after_push = true;
                    ref_is_empty_result_before_pop = false;
                    ref_pop_status = true;
                    ref_is_empty_result = false;
                    ref_is_full_before_pop = false;
                    ref_is_full_after_pop = false;
                    ref_is_full_result = false;
                    break;
                case STACK_SIZE:
                    s1.push(STACK_SIZE);
                    ref_pop_value = STACK_SIZE;
                    ref_pop_value_before_push = ref_pop_value;
                    ref_is_empty_result_before_pop = false;
                    ref_pop_status = true;
                    ref_is_full_before_pop = true;
                    ref_is_full_after_pop = true;
                    ref_is_full_after_push = true;
                    ref_is_full_result = true;
                    ref_is_empty_result = false;
                    ref_push_result = false;
                    break;
                default:
                    std::cout << "Stack size unknown," << " stack_size = " << static_cast<int>(state) << std::endl;
            }

            bool push_result {false};
            int pop_value {0};
            bool pop_status {false};
            bool is_full_result {false};
            bool is_empty_result {false};

            // queue markers
            bool pop_before_push {false};
            bool pop_before_is_empty {false};
            bool push_before_is_empty {false};

            bool push_was_called {false};
            bool pop_was_called {false};

            for (auto &num: functions) {
                switch (num) {
                    case 1:
                        push_was_called = true;
                        if (!pop_was_called) {
                            pop_before_push = false;
                            if (state == STACK_SIZE) {
                                break;
                            }
                        }
                        push_result = s1.push(push_value);
                        break;
                    case 2:
                        pop_was_called = true;
                        if (!push_was_called) {
                            pop_before_push = true;
                        }
                        try {
                            pop_value = s1.pop();
                            pop_status = true;
                        }
                        catch (std::runtime_error &error) {
                            pop_status = false;
                        }
                        break;
                    case 3:
                        if (push_was_called)
                            push_before_is_empty = true;
                        if (pop_was_called)
                            pop_before_is_empty = true;
                            is_empty_result = s1.is_empty();
                        break;
                    default:
                        std::cout<< "Check variable functions" << std::endl;
                    } //switch
                } // for
            
            std::cout << std::boolalpha;
            
            switch (state) {

                case 0:

                    if (ref_push_result != push_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted push_result = " << true << ", actual push_result = " << push_result << std::endl;
                    if (!pop_before_push && (pop_value != push_value || !pop_status))
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << push_value << ", actual pop_value = " << pop_value << std::endl;
                    if (ref_is_full_result != is_full_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted full_result = " << false << ", actual full_result = " << is_full_result << std::endl;
                    if (pop_before_push && push_before_is_empty && is_empty_result != false)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted is_empty_result = " << false << ", actual is_empty_result = " << is_empty_result << std::endl;
                    if (!pop_before_push && push_before_is_empty && pop_before_is_empty && is_empty_result != true)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted is_empty_result = " << true << ", actual is_empty_result = " << is_empty_result << std::endl;
                    if (!push_before_is_empty && is_empty_result != true)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted is_empty_result = " << true << ", actual is_empty_result = " << is_empty_result << std::endl;
                    if (pop_before_push == true)
                        s1.pop();
                    break;
                case 1:

                    if ((pop_value != ref_pop_value_before_push && pop_before_push) || !pop_status)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << ref_pop_value_before_push << ", actual pop_value = " << pop_value << std::endl;
                    if (!pop_status || (pop_value != push_value && !pop_before_push))
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << push_value << ", actual pop_value = " << pop_value << std::endl;
                    if (ref_push_result != push_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted push_result = " << true << ", actual push_result = " << push_result << std::endl;
                    if (ref_is_full_result != is_full_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted full_result = " << false << ", actual full_result = " << is_full_result << std::endl;
                    if (pop_before_is_empty && !push_before_is_empty && is_empty_result != true)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " <<
                        get_order_of_calls(functions) << ", wanted is_empty_result = " << true << ", actual is_empty_result = " << is_empty_result << std::endl;
                    if (!(pop_before_is_empty && !push_before_is_empty) && is_empty_result != false)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " <<
                        get_order_of_calls(functions) << ", wanted is_empty_result = " << false << ", actual is_empty_result = " << is_empty_result << std::endl;
                    s1.pop();
                    break;
                case STACK_SIZE/2:

                    if ((pop_value != ref_pop_value_before_push && pop_before_push) || !pop_status)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << ref_pop_value_before_push << ", actual pop_value = " << pop_value << std::endl;
                    if (!pop_status || (pop_value != push_value && !pop_before_push))
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << push_value << ", actual pop_value = " << pop_value << std::endl;
                    if (ref_push_result != push_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted push_result = " << true << ", actual push_result = " << push_result << std::endl;
                    if (is_empty_result != ref_is_empty_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted is_empty_result = " << false << ", actual is_empty_result = " << is_empty_result << std::endl;
                    if (ref_is_full_result != is_full_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted full_result = " << false << ", actual full_result = " << is_full_result << std::endl;
                    s1.pop();
                    break;
                case STACK_SIZE-1:

                    if ((pop_value != ref_pop_value_before_push && pop_before_push) || !pop_status)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << ref_pop_value_before_push << ", actual pop_value = " << pop_value << std::endl;
                    if (!pop_status || (pop_value != push_value && !pop_before_push))
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << push_value << ", actual pop_value = " << pop_value << std::endl;
                    if (ref_push_result != push_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted push_result = " << true << ", actual push_result = " << push_result << std::endl;
                    if (is_empty_result != ref_is_empty_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted is_empty_result = " << false << ", actual is_empty_result = " << is_empty_result << std::endl;
                    s1.pop();
                    break;
                case STACK_SIZE:

                    if (pop_value != ref_pop_value || !pop_status)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted pop_status = " << true << ", actual pop_status = " << pop_status << ", wanted pop_value = " << ref_pop_value << ", actual pop_value = " << pop_value << std::endl;
                    if (pop_before_push && push_result != true)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted push_result = " << true << ", actual push_result = " << push_result << std::endl;
                    /* is_empty/is_full –> push –> pop */
                    if (!pop_before_push && push_result != false)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted push_result = " << false << ", actual push_result = " << push_result << std::endl;
                    if (is_empty_result != ref_is_empty_result)
                        std::cout << "[FAILED " << __LINE__ << "] state = " << static_cast<int>(state) << ", calls = " << get_order_of_calls(functions) << ", wanted is_empty_result = " << ref_is_empty_result << ", actual is_empty_result = " << is_empty_result << std::endl;
                    if (pop_before_push == true)
                        s1.pop();

                    break;
            } // switch
        } while (std::next_permutation(functions.begin(), functions.end()));
    } // for

    std::cout << "Test ok" << std::endl;
    return 0;
}
