#include <iostream>

using namespace std;

struct StrWithCount {
    string str;
    int count;
};

string Croatia[8] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };

StrWithCount TaskString(StrWithCount target, string str) {
    int index = target.str.find(str);
    if (index == -1)
        return target;
    
    target.str.erase(index, str.length());
    target.count++;

    return TaskString(target, str);
}

int CountingWithCroatia(string input) {

    StrWithCount st = { input, 0 };
    for (int i = 0; i < 8; i++)
        st = TaskString(st, Croatia[i]);
    
    return st.count + st.str.length();
}

int main()
{
    string input;
    cin >> input;
    cout << CountingWithCroatia(input) << endl;
    return 0;
}