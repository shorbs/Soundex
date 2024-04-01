#include "soundex.h"

int main(){
    SoundexCypher cypher;
    string str;
    cin >> str;
    cout << cypher.soundex(str);
    return 0;
}