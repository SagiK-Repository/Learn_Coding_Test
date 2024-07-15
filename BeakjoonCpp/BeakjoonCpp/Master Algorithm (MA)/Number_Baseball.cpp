#include <iostream>
#include <vector>

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

static string ChoiseString(string input, int choise1 = -1, int choise2 = -1) {
    string output = "xxx";
    if (choise1 != -1)
        output[choise1] = input[choise1];
    if (choise2 != -1)
        output[choise2] = input[choise2];
    return output;
}

static int Predicted_Cases(vector<BaseBall> input)
{
    vector<TreeNode> answers;
    for (const auto& question : input) {
        if (question.strike == 0 && question.ball == 0) {
            vector<int> exceptNumbers = ConvertStringToVector(question.number);
            TreeNode answer{ "xxx", exceptNumbers, exceptNumbers, exceptNumbers };
        }
        else if (question.strike == 1 && question.ball == 0) {
            for (int i = 0; i < 3; i++) {
                string rightData = ChoiseString(question.number, i);
                vector<int> rightException = ConvertStringToVector(rightData);
                vector<int>  questionException = ConvertStringToVector(question.number);
                TreeNode answer{ rightData, GenerateNumbersExcept(rightException), GenerateNumbersExcept(questionException) , GenerateNumbersExcept(questionException) };
            }
        }
    }
    //    for (int strike = 0; strike < question.strike; strike++)
    //        for(int ball = 0; ball < question.ball; ball++)


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