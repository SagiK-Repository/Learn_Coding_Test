#include <iostream>
#include <vector>

using namespace std;

int Factorial(int num) {
    if (num <= 1) return 1;
    return num * Factorial(num - 1);
}

struct Counter
{
    int three, tow, one;

    int GetCount() const {
        if (three == 0 && tow == 0 && one == 0)
            return 0;

        return (int)(
            Factorial(three + tow + one) /
            (Factorial(three) * Factorial(tow) * Factorial(one)));;
    }
};

int CountNumber(int number) {
    vector<vector<Counter>> matrix((int)(number / 3) + 1, vector<Counter>((int)(number / 2) + 1));
    int count = 0;

    for (int i = 0; i < matrix.size(); ++i)
        for (int j = 0; j < matrix[i].size(); ++j)
            if (number - (3 * i) - (2 * j) >= 0)
                matrix[i][j] = Counter{ i, j, number - (3 * i) - (2 * j) };
    
    for (auto i : matrix)
        for (auto j : i)
            count += j.GetCount();

    return count;
}

int main()
{
    int repeat, input;
    cin >> repeat;

    vector<int> answers;

    for (int index = 0; index < repeat; index++)
    {
        cin >> input;
        answers.push_back(CountNumber(input));
    }

    for (const auto& answer : answers)
        cout << answer << endl;
    return 0;
}