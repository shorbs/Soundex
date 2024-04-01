#include "soundex.h"

using namespace std;

SoundexCypher::SoundexCypher()
{
    this->str = "";
    this->first_char = ' ';
}
//
string SoundexCypher::soundex(string s)
{
    //prepStr the input string which will remove all nonAlpha chars and set the string to ALLCAPS
    this->str = stringToSoundexNums(prepStr(s));
    //regex to remove all ocurrences of H W and Y
    regex soundex_remove_hwy("[7]");
    str = regex_replace(str, soundex_remove_hwy, "");
    //regex to find all occurences of adjacent characters
    regex soundex_adj1("([1-6])\\1+");
    //regex_replace will keep the first character in the string of recurring characters
    str = regex_replace(str, soundex_adj1, "$1");
    //at this point we want to put our first letter back in
    //if the first char is a vowel, replace first index with first letter
    if (str[0] != '0')
    {
        str[0] = first_char;
    }
    //if the first char is anything else, insert before the rest of the string
    else
    {
        str = first_char + str;
    }
    //once all of the adjacent sounds and similar sounds seperated by an HWY are removed
    //  remove all the vowels or "0"'s
    regex soundex_remove_zeros("[0]");
    str = regex_replace(str, soundex_remove_zeros, "");
    //resize so it is 4 chars long
    str = resize(str);
    return str;
}

string SoundexCypher::prepStr(string s)
{
    //regex for all non non alpha chars
    regex kill_non_alpha("[^a-zA-Z]");
    s = regex_replace(s, kill_non_alpha, "");
    //then we turn up! string toUpper loop thang    
    for (auto &c : s)
    {
        c = toupper(c);
    }
    //save that first character that is definitley alpha and UPPER, we will use it later...
    first_char = s[0];
    return s;
}

string SoundexCypher::stringToSoundexNums(string s)
{
    //This is just the regex I made for the soundex encoding
    //  theres probably a way to 1 line this entire assignment using regex
    //  but I feel as though this is easier to read nad understand

    //I needed to implement a special case for HWY becasue if an HWY is 
    //  sandwiched between similar sounds then we only save the first of those similar sounds, 
    //  or second. doesn't actually matter too much
    regex soundex_0("[AEIOU]");
    regex soundex_1("[BFPV]");
    regex soundex_2("[CGJKQSXZ]");
    regex soundex_3("[DT]");
    regex soundex_4("[L]");
    regex soundex_5("[MN]");
    regex soundex_6("[R]");
    regex soundex_hwy("[HWY]");

    //str_after is just a temp variable for my numerical SOUNDEX REGEX AWSOMENESS
    string str_after = regex_replace(s, soundex_0, "0");
    str_after = regex_replace(str_after, soundex_1, "1");
    str_after = regex_replace(str_after, soundex_2, "2");
    str_after = regex_replace(str_after, soundex_3, "3");
    str_after = regex_replace(str_after, soundex_4, "4");
    str_after = regex_replace(str_after, soundex_5, "5");
    str_after = regex_replace(str_after, soundex_6, "6");
    str_after = regex_replace(str_after, soundex_6, "6");
    str_after = regex_replace(str_after, soundex_hwy, "7");
    return str_after;
}

string SoundexCypher::resize(string s)
{
    //if its more than four.... cut the rest off
    if (s.size() > 4)
        s = s.substr(0, 4);
    //if its less than four.... fill it with '0's
    if (s.size() < 4)
        s += string(4 - s.size(), '0');
    return s;
}