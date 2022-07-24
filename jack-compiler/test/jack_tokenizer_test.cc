#include "jack_tokenizer.h"

#include <gtest/gtest.h>
#include <queue>

using std::queue;

TEST(TokenizerTest, Advance)
{
    Jacktokenizer tokenizer("Square/SquareGame.jack");
    // queue<string> tokens; 
    // tokens.push("class");
    // tokens.push("SquareGame");
    // tokens.push("{");
    // tokens.push("field");
    // tokens.push("Square");
    // tokens.push("square");
    // tokens.push(";");
    // tokens.push("field");
    // tokens.push("int");
    // tokens.push("direction");
    // tokens.push(";");
    // while (tokenizer.hasMoreTokens() && !tokens.empty())
    // {
    //     tokenizer.advance();
    //     EXPECT_EQ(tokenizer.current_token(), tokens.front());
    //     tokens.pop();
    // }
    while (tokenizer.hasMoreTokens())
    {
        tokenizer.advance();
        std::cout << tokenizer.current_token() << std::endl;
    }
}