#include "jack_tokenizer.h"

#include <gtest/gtest.h>

TEST(TokenizerTest, Advance)
{
    Jacktokenizer tokenizer("Square/Main.jack");
    if (tokenizer.hasMoreTokens())
    {
        tokenizer.advance();
    }
}