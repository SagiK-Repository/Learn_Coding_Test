#include <iostream>
#include <string>

using namespace std;

char Decryption(char input)
{
    int index = input - 'A';
    int passer = (index - 3) % 26;
    if (passer < 0) passer = 26 + passer;
    return 'A' + passer;
}

int main()
{
    string input;
    cin >> input;

    for (const auto& word : input)
        cout << Decryption(word);

    return 0;
}