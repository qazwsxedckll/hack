#include "jack_analyzer.h"

#include <gtest/gtest.h>

TEST(AnalyzerTest, IsJackFile)
{
    EXPECT_TRUE(IsJackFile("test.jack"));
    EXPECT_FALSE(IsJackFile("test.test"));
    EXPECT_FALSE(IsJackFile("test"));
}