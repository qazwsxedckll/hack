#include "compilation_engine.h"

#include <iostream>

using namespace std;

CompilationEngine::CompilationEngine(const string& input, const string& output) :
    input_file_(input),
    output_file_(output)
{
    if (!input_file_) {
        cout << "Jacktokenizer: Failed to open file(" << input << ")" << endl;
        exit(1);
    }
    if (!output_file_) {
        cout << "Jacktokenizer: Failed to open file(" << output << ")" << endl;
        exit(1);
    }
}