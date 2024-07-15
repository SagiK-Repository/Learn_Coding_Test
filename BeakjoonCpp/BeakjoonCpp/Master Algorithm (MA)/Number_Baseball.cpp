#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct BaseBall {
    string number;
    int strike;
    int ball;
};

struct TreeNode {
    string data;
    vector<int> noneOne;
    vector<int> noneTwo;
    vector<int> noneThree;
    vector<TreeNode*> children;

    TreeNode(string dara
           , vector<int> noneOne
           , vector<int> noneTwo
           , vector<int> noneThree) : data(data), noneOne(noneOne), noneTwo(noneTwo), noneThree(noneThree) {}
};

static vector<int> ConvertStringToVector(const string& str) {
    vector<int> result;
    for (char c : str)
        if (c != 'x')
            result.push_back(c - '0');
    return result;
}

static vector<int> GenerateNumbersExcept(const vector<int>& exclude) { // const : 변경 불가능, & : 복사해서 가져오지 않고, 원본을 가져온다.
    vector<int> result;
    for (int i = 0; i < 10; i++)
        if (find(exclude.begin(), exclude.end(), i) == exclude.end())
            result.push_back(i);
    return result;
}

static string ChoiseString(string input, bool choise1, bool choise2, bool choise3) {
    string output = "xxx";
    if (choise1)
        output[0] = input[0];
    if (choise2)
        output[1] = input[1];
    if (choise3)
        output[2] = input[2];
    return output;
}

static int Predicted_Cases(vector<BaseBall> input)
{
    vector<TreeNode> answers;
    for (const auto& question : input) {
        if (question.strike == 0 && question.ball == 0) { // ball이 0 ~ 3
            vector<int> exceptNumbers = ConvertStringToVector(question.number);
            TreeNode answer{ "xxx", exceptNumbers, exceptNumbers, exceptNumbers };
            answers.push_back(answer);
        }
        else if (question.strike == 1 && question.ball == 0) { // ball이 0~2
            for (int i = 0; i < 3; i++) {
                string rightData = ChoiseString(question.number, i == 0, i == 1, i == 2);
                vector<int> rightException = ConvertStringToVector(rightData);
                vector<int>  questionException = ConvertStringToVector(question.number);
                TreeNode answer{ rightData, i == 0 ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException)
                                          , i == 1 ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException)
                                          , i == 2 ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException) };
                answers.push_back(answer);
            }
        }
        else if (question.strike == 2 && question.ball == 0) { // ball이 0 아니면 1
            int index = 1;
            for (int i = 0; i < 3; i++) {
                string rightData = ChoiseString(question.number, i < 2, i != 2, i > 0);
                vector<int> rightException = ConvertStringToVector(rightData);
                vector<int> questionException = ConvertStringToVector(question.number);
                TreeNode answer{ rightData, i < 2 ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException)
                                          , i != 2? GenerateNumbersExcept(questionException) : GenerateNumbersExcept(questionException)
                                          , i > 0 ? GenerateNumbersExcept(questionException) : GenerateNumbersExcept(questionException) };
                answers.push_back(answer);
            }
        }
        else if (question.strike == 3)
        {
            string rightData = question.number;
            vector<int> rightException = ConvertStringToVector(rightData);
            TreeNode answer{ rightData, GenerateNumbersExcept(rightException), GenerateNumbersExcept(rightException) , GenerateNumbersExcept(rightException) };
            answers.push_back(answer);
        }
    }

    return 0;
}

int main()
{
    int repeat;
    cin >> repeat;

    vector<BaseBall> questions;

    for (int index = 0; index < repeat; index++) {
        BaseBall question{};
        cin >> question.number >> question.strike >> question.ball;
        questions.push_back(question);
    }

    cout << Predicted_Cases(questions);

    return 0;
}