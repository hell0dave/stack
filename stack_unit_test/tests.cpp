#include <gtest/gtest.h>
#include "stack.h"

TEST(Constructors, DefaultConstructor) {
    stack a;
}

//TEST(Constructors, CopyConstructor) {
//    stack a;
////    stack b(a);
//}

TEST(Constructors, MoveConstructor) {
    stack a;
    int32_t p {5};
    a.push(p);
    stack b(std::move(a));
    EXPECT_EQ(p, b.pop());
    EXPECT_TRUE(a.is_empty());
}

//TEST(Constructors, Is_emptyConstructor) {
//    stack a;
//    a.is_empty();
//}
//
//TEST(Constructors, PushConstructor) {
//    stack a;
//    a.push(4);
//}
//
//TEST(Constructors, PopConstructor) {
//    stack a;
//    a.pop();
//}
