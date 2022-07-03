#include "jack_tokenizer.h"

#include <gtest/gtest.h>

TEST(TokenizerTest, Advance)
{
    Jacktokenizer tokenizer("Square/SquareGame.jack");
    for (int i = 0; i < 10; i++)
    {
        if (tokenizer.hasMoreTokens())
        {
            tokenizer.advance();
        }
    }
}