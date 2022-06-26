#ifndef JACK_ANALYZER_H_
#define JACK_ANALYZER_H_

#include <string>

bool IsJackFile(const std::string& file_name);

int Analyze(const std::string& file_name);

#endif // !JACK_ANALYZER_H_