#include "utils.h"
#include "jack_tokenizer.h"

#include <iostream>

#include <dirent.h>

using namespace std;

int main(int argc, char* argv[])
{
    string input;
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    } else {
        input = argv[1];
        if (IsJackFile(input)) {
            Jacktokenizer tokenizer(input); 
            return 0;
        } else {
            auto dir = opendir(argv[1]);
            if (dir == NULL) {
                cout << "cannot open directory: " << argv[1] << endl;
                return -1;
            }

            if (input.back() == '/') {
                input = input.substr(0, input.length() - 1);
            }
            auto entity = readdir(dir);
            string file_path;
            while (entity != NULL) {
                file_path = input + "/" + entity->d_name;
                if (IsJackFile(file_path)) {
                }
                entity = readdir(dir);
            }
            return 0;
        }
    }
}
