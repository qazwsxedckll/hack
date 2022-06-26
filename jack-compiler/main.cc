#include "jack_tokenizer.h"
#include "jack_analyzer.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    }
    else
    {
        Analyze(argv[1]); 
    }
}
