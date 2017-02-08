#include "gcd.h"
#include "gtest/gtest.h"

TEST(cpp_gcd_test, 2_3)
{
    EXPECT_EQ(1, gcd(2,3));
}
