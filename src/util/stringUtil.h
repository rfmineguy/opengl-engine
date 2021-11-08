#include <sstream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

inline void eraseCharacters(std::string& s, std::string chars) {
    for (unsigned int i = 0; i < chars.size(); i++) {
        s.erase(std::remove(s.begin(), s.end(), chars.at(i)), s.end());
    }
}

inline int charToInt(char c) {
    return static_cast<int>(c);
}

inline std::vector<std::string> splitBy(std::string s, char delim) {
    std::vector<std::string> vec;
    std::stringstream ss(s);
    std::string token;

    while(getline(ss, token, delim)) {
        vec.push_back(token);
    }
    return vec;
}
