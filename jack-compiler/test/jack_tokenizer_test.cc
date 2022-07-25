#include "jack_tokenizer.h"

#include <gtest/gtest.h>
#include <queue>

using std::queue;

TEST(TokenizerTest, ValidIdentifier)
{
    EXPECT_TRUE(Jacktokenizer::ValidIdentifier("test123_"));
    EXPECT_TRUE(Jacktokenizer::ValidIdentifier("_test123"));
    EXPECT_FALSE(Jacktokenizer::ValidIdentifier("123test_"));
    EXPECT_FALSE(Jacktokenizer::ValidIdentifier("test123$_"));
}

TEST(TokenizerTest, Advance)
{
    Jacktokenizer tokenizer("Square/Main.jack");
    while (tokenizer.hasMoreTokens())
    {
        tokenizer.advance();
        std::cout << tokenizer.current_token() << std::endl;
    }
}