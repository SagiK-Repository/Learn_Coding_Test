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
    vector<string> noneDatas;
    vector<TreeNode*> children;

    TreeNode(string dara, vector<string> noneDatas) : data(data), noneDatas(noneDatas) {}
};


int Predicted_Cases(vector<BaseBall> input)
{
    for (const auto& question : input)
        cout << question.number << endl;

    return 0;
}

int main()
{
    int repeat;
    cin >> repeat;

    vector<BaseBall> questions;

    for (int index = 0; index < repeat; index++)
    {
        BaseBall question{};
        cin >> question.number >> question.strike >> question.ball;
        questions.push_back(question);
    }

    cout << Predicted_Cases(questions);

    return 0;
}