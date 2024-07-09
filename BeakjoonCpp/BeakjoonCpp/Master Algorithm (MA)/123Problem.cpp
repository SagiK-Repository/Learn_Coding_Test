#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool AddNumber(int* array, int length, int pos)
{
    if (array[pos] == 2 && array[pos + 1] == 2 && array[pos + 2] == 2) {
        array[pos] = 0;
        array[pos + 1] = 1;
        array[pos + 2] = 1;
        return true;
    }
    else if (array[pos] == 1 && array[pos + 1] == 1 && array[pos + 2] == 0) {
        array[pos] = 2;
        array[pos + 1] = 2;
        array[pos + 2] = 2;
        return true;
    }
    else if (array[pos] == 0 && array[pos + 1] == 0) {
        array[pos]++;
        array[pos + 1]++;
        return true;
    }
    return false;
}

void AddArray(int* array, int number, int& count)
{
    int pos = 0, decpos = 0;
    while (true) {
        if (AddNumber(array, number, pos)) {
            count++;
            continue;
        }
        else if (pos + 3 < decpos)
        {
            AddArray(array, decpos, count);
            pos++;
            continue;
        }
        else if (decpos + 2 == number) {
            break;
        }
        else if (AddNumber(array, number, decpos)) {
            pos = 0;
            for (int zero = 0; zero < decpos; zero++)
                array[zero] = 0;
            count++;
            continue;
        }
        decpos++;
    }
}

int CountNumber(int number) {
    int count = 1; // 1+1+...+1+1
    int* array = new int[number]();

    AddArray(array, number, count);
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