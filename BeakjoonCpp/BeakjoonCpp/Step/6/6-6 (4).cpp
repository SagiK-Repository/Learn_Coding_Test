#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> Croatia = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };

string TaskString(string target, string str) {
    int index = target.find(str);
    if (index == -1)
        return target;

    target.replace(index, str.length(), "#");

    return TaskString(target, str);
}

int CountingWithCroatia(string input) {
    for (const auto& croatian : Croatia)
        input = TaskString(input, croatian);

    return input.length();
}

int main()
{
    string input;
    cin >> input;
    cout << CountingWithCroatia(input) << endl;
    return 0;
}