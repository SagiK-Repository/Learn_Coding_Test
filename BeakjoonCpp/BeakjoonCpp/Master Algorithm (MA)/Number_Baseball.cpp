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
    vector<string> noneOne;
    vector<string> noneTwo;
    vector<string> noneThree;
    vector<TreeNode*> children;

    TreeNode(string dara
           , vector<string> noneOne
           , vector<string> noneTwo
           , vector<string> noneThree) : data(data), noneOne(noneOne), noneTwo(noneTwo), noneThree(noneThree) {}
};

int Predicted_Cases(vector<BaseBall> input)
{
    vector<TreeNode> ansewers;
    for (const auto& question : input)
    {
        if (question.strike == 0 && question.ball == 0)
        {
            TreeNode ansewer{"xxx", };
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

    for (int index = 0; index < repeat; index++)
    {
        BaseBall question{};
        cin >> question.number >> question.strike >> question.ball;
        questions.push_back(question);
    }

    cout << Predicted_Cases(questions);

    return 0;
}