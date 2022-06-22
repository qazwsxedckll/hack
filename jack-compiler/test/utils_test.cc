#include "utils.h"

#include <gtest/gtest.h>

TEST(UtilsTest, IsJackFile)
{
    EXPECT_EQ(IsJackFile("test.jack"), true);
    EXPECT_EQ(IsJackFile("test.test"), false);
    EXPECT_EQ(IsJackFile("test"), false);
}