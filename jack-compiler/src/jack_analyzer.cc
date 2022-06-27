#include "jack_analyzer.h"
#include "jack_tokenizer.h"
#include "compilation_engine.h"

#include <filesystem>

using namespace std;

bool IsJackFile(const string& file_name)
{
    auto dot_pos = file_name.find_last_of(".");
    if (dot_pos == string::npos)
    {
        return false;
    }

    if (file_name.substr(dot_pos) == ".jack")
    {
        return true;
    }

    return false;
}

int Analyze(const string& file_name)
{
    const std::filesystem::path input(file_name);
    if (IsJackFile(input))
    {
        Jacktokenizer tokenizer(input);
        const std::filesystem::path output(input.filename().replace_extension(".xml"));
        CompilationEngine engine(input, output); 
        while (tokenizer.hasMoreTokens())
        {
            tokenizer.advance();
        }
        return 0;
    }
    else
    {
        // auto dir = opendir(argv[1]);
        // if (dir == NULL) {
        //     cout << "cannot open directory: " << argv[1] << endl;
        //     return -1;
        // }

        // if (input.back() == '/') {
        //     input = input.substr(0, input.length() - 1);
        // }
        // auto entity = readdir(dir);
        // string file_path;
        // while (entity != NULL) {
        //     file_path = input + "/" + entity->d_name;
        //     if (IsJackFile(file_path)) {
        //     }
        //     entity = readdir(dir);
        // }
        return 0;
    }
}