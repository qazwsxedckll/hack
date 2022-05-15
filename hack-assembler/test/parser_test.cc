#include "parser.h"

#include "gtest/gtest.h"

#include <regex>

TEST(SymbolTest, SymbolLegitment)
{
    string file_path = __FILE__;
    string dir_path = file_path.substr(0, file_path.rfind("/"));
    Parser parser(dir_path + "/empty.asm");
    EXPECT_TRUE(parser.is_legit("test"));
    EXPECT_TRUE(parser.is_legit("test123:_."));
    EXPECT_FALSE(parser.is_legit("1test"));
}