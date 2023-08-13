#include "algs.h"
#include <iostream>
#include "gtest/gtest.h"

class AlgTest : public testing::Test {
protected:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(AlgTest, mySum)
{
    EXPECT_EQ(Solution().mySum(1, 2), 3);
}