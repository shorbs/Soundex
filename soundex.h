#ifndef SOUNDEXCYPHER_H
#define SOUNDEXCYPHER_H

#include <iostream>
#include <regex>

using namespace std;

class SoundexCypher
{
    public:
        SoundexCypher();
        string soundex(string s);
    private:
    string str;
    char first_char;
    string prepStr(string s);
    string stringToSoundexNums(string s);
    string resize(string s);
};

#endif