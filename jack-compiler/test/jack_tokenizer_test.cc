#include "jack_tokenizer.h"

#include <gtest/gtest.h>

TEST(TokenizerTest, Advance)
{
    Jacktokenizer tokenizer("Square/SquareGame.jack");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, "class");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, "SquareGame");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, "{");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, "field");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, "Square");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, "square");
    tokenizer.advance();
    EXPECT_EQ(tokenizer.current_token_, ";");
}