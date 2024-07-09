#include <iostream>

using namespace std;

string Croatia[8] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };

int CountOfCharacter(string input) {
    int count = 0;
    string findString = input;
    bool isHaveCroatia = false;
    while (findString != "") {
        isHaveCroatia = false;
        for (int i = 0; i < 8; i++) {
            int index = findString.find(Croatia[i]);
            if (index == -1)
                continue;
            isHaveCroatia = true;
            findString.erase(index, Croatia[i].length());
            count++;
        }
        if (isHaveCroatia == false)
        {
            count++;
            findString.erase(0, 1);
        }
    }
    return count;
}

int main()
{
    string input;
    cin >> input;

    cout << CountOfCharacter(input) << endl;

    return 0;
}