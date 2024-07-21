#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

struct BaseBall {
    string number;
    int strike;
    int ball;
};

struct TreeNode {
    string data;
    vector<int> nones[3] = {};

    vector<TreeNode> children;

    TreeNode(string dara
           , vector<int> noneOne
           , vector<int> noneTwo
           , vector<int> noneThree) : data(data), nones{ noneOne, noneTwo, noneThree } {}

    int GetCount() {
        int one = 10 - nones[0].size();
        int two = 10 - nones[1].size();
        int three = 10 - nones[2].size();
        return one * two * three;
    }
};

static vector<int> ConvertStringToVector(const string& str) {
    vector<int> result;
    for (char c : str)
        if (c != 'x')
            result.push_back(c - '0');
    return result;
}

static vector<int> GenerateNumbersExcept(const vector<int>& exclude) { // const : ���� �Ұ���, & : �����ؼ� �������� �ʰ�, ������ �����´�.
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

static TreeNode GetTree(string number, bool first, bool second, bool third) {
    string rightData = ChoiseString(number, first, second, third);
    vector<int> rightException = ConvertStringToVector(rightData);
    vector<int>  questionException = ConvertStringToVector(number);
    TreeNode answer{ rightData, first ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException)
                              , second ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException)
                              , third ? GenerateNumbersExcept(rightException) : GenerateNumbersExcept(questionException) };
    return answer;
}

static void ExceptNumber(vector<int>& input, char exceptNum) {
    input.erase(remove(input.begin(), input.end(), exceptNum - '0'), input.end());
}

static bool FindNumber(vector<int> input, char findNum) {
    return find(input.begin(), input.end(), findNum - '0') != input.end();
}

static vector<TreeNode> GetBallTree(TreeNode strike, int ball) {
    vector<TreeNode> trees;
    if (ball == 0)
        trees.push_back(strike);
    else if (ball == 1)
        for (int i = 0; i < 3; i++) {
            if (strike.data[i] == 'x') {
                TreeNode data(strike);
                if (i == 0) {
                    ExceptNumber(data.nones[1], data.data[i]);
                    ExceptNumber(data.nones[2], data.data[i]);
                }
                else if (i == 1) {
                    ExceptNumber(data.nones[0], data.data[i]);
                    ExceptNumber(data.nones[2], data.data[i]);
                }
                else if (i == 2) {
                    ExceptNumber(data.nones[0], data.data[i]);
                    ExceptNumber(data.nones[1], data.data[i]);
                }
                trees.push_back(data);
            }
        }
    else if (ball == 2)
        for (int i = 0; i < 3; i++) {
            if (strike.data[i] != 'x') {
                TreeNode data(strike);
                if (i == 0) {
                    ExceptNumber(data.nones[1], data.data[3]);
                    ExceptNumber(data.nones[2], data.data[2]);
                }
                else if (i == 1) {
                    ExceptNumber(data.nones[0], data.data[3]);
                    ExceptNumber(data.nones[2], data.data[1]);
                }
                else if (i == 2) {
                    ExceptNumber(data.nones[0], data.data[2]);
                    ExceptNumber(data.nones[1], data.data[1]);
                }
                trees.push_back(data);
            }
        }
    else if (ball == 3)
        for (int i = 0; i < 3; i++) {
            if (strike.data[i] == 'x') {
                TreeNode data(strike);
                if (i == 0) {
                    continue;
                }
                else if (i == 1) {
                    ExceptNumber(data.nones[0], data.data[2]);
                    ExceptNumber(data.nones[1], data.data[0]);
                    ExceptNumber(data.nones[2], data.data[1]);
                }
                else if (i == 2) {
                    ExceptNumber(data.nones[0], data.data[1]);
                    ExceptNumber(data.nones[1], data.data[2]);
                    ExceptNumber(data.nones[2], data.data[0]);
                }
                trees.push_back(data);
            }
        }
    return trees;
}

static bool CanJoin(TreeNode parentTree, TreeNode tree) {
    bool can = false;
    for (int i = 0; i < 3; i++) {
        can &= (parentTree.data[i] == 'x' || tree.data[i] == 'x' || parentTree.data[i] == tree.data[i]);
    }
    return can;
}

static void AddAnswer(vector<TreeNode>& answers, TreeNode tree) {
    
    for (auto& answer : answers) {
        if (CanJoin(answer, tree)) {
            if (answer.children.size() == 0)
                answer.children.push_back(tree);
            for (auto& answerChildren : answer.children)
                AddAnswer(answer.children, tree);
        }
    }
}

static void UpdateCountTree(TreeNode answer, TreeNode& count) {
    for (int i = 0; i < 3; i++) {
        if (answer.data[i] != 'x')
            count.data[i] = answer.data[i];

        for (auto ddd : answer.nones[i]) {
            if (find(count.nones[i].begin(), count.nones[i].end(), ddd) == count.nones[i].end())
                count.nones[i].push_back(ddd);
        }
    }
}

static int TreeCount(int& count, TreeNode answer, TreeNode& countTree) {
    if (CanJoin(answer, countTree) == false)
        return count;

    UpdateCountTree(answer, countTree);

    if (answer.children.size() == 0) {
        return count + countTree.GetCount();
    }
    else {
        for (auto& children : answer.children) {
            TreeCount(count, children, countTree);
        }
    }
}

static int CanCount(vector<TreeNode> answers) {
    int count = 0;

    for (auto answer : answers) {
        TreeNode countTree("xxx", vector<int>(), vector<int>(), vector<int>());
        TreeCount(count, answer, countTree);
    }

    return count;
}

static int Predicted_Cases(vector<BaseBall> input)
{
    vector<TreeNode> answers;
    for (const auto& question : input) {
        vector<TreeNode> canTree;
        if (question.strike == 0) {
            TreeNode tree = GetTree(question.number, false, false, false);
            
            for (auto t : GetBallTree(tree, question.ball))
                canTree.push_back(t);
        }
        else if (question.strike == 1) { // ball 0 -> x, 1 -> 2, 2 -> 1경우
            for (int i = 0; i < 3; i++) {
                TreeNode tree = GetTree(question.number, i == 0, i == 1, i == 2);

                for (auto t : GetBallTree(tree, question.ball))
                    canTree.push_back(t);
            }
        }
        else if (question.strike == 2) { // ball 1 불가능
            int index = 1;
            for (int i = 0; i < 3; i++) {
                TreeNode tree = GetTree(question.number, i <2, i != 2, i > 0);
                canTree.push_back(tree);
            }
        }
        else if (question.strike == 3)
        {
            TreeNode tree = GetTree(question.number, true, true, true);
            
            canTree.push_back(tree);
        }

        for (auto tree : canTree) {
            AddAnswer(answers, tree);
        }
    }

    return CanCount(answers);
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