#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct StrWithCount {
    string str;
    int count;
    
    void Erase(int index, string eraseStr) {
        str.erase(index, eraseStr.length());
        count++;
    }
};

const vector<string> Croatia = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };

StrWithCount TaskString(StrWithCount target, string str) {
    int index = target.str.find(str);
    if (index == -1)
        return target;

    target.Erase(index, str);

    return TaskString(target, str);
}

int CountingWithCroatia(string input) {
    StrWithCount st = { input, 0 };
    for (const auto& croatian : Croatia)
        st = TaskString(st, croatian);

    return st.count + st.str.length();
}

int main()
{
    string input;
    cin >> input;
    cout << CountingWithCroatia(input) << endl;
    return 0;
}