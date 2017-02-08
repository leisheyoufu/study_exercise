#include "hello.h"
#include "gtest/gtest.h"

namespace death {

class HelloWorldTest : public ::testing::Test {
public:
    HelloWorldTest() {}
protected:
};

TEST(HelloWorldTest, hello)
{
    HelloWorld hw;
    EXPECT_EQ("hello world", hw.SayHello());
}

TEST(HelloWorldDeathTest, die)
{
    HelloWorld hw;
    ASSERT_DEATH(hw.Die(), "");
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
