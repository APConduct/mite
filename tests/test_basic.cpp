#include <gtest/gtest.h>

// Simple test to verify Google Test is working
TEST(BasicTest, SimpleAssertion) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_TRUE(true);
}

TEST(BasicTest, StringComparison) {
    std::string hello = "Hello";
    std::string world = "World";
    EXPECT_NE(hello, world);
}
