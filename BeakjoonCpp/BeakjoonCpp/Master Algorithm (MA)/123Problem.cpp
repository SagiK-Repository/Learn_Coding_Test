#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    Node(const int data) : data(data) { }

public:
    const int data;
    Node* left;
    Node* right;
};

int Factorial(int num) {
    if (num <= 1) return 1;
    return num * Factorial(num - 1);
}

struct Counter
{
    int three, tow, one;

    int GetCount() const {
        return (int)(
                            Factorial(three + tow + one) /
                (Factorial(three) + Factorial(tow) + Factorial(one))
            );
    }
};

Node* CreateThreeNode() {
    Node* threeNode = new Node(3);
    Node* twoNode = new Node(2);
    threeNode->left = twoNode;
    threeNode->right = new Node(1);
    twoNode->left = new Node(1);
    twoNode->right = new Node(1);
    return threeNode;
}

Node* CreateTwoNode() {
    Node* twoNode = new Node(2);
    twoNode->left = new Node(1);
    twoNode->right = new Node(1);
    return twoNode;
}

vector<Node*> CreateMap(int number) {
    vector<Node*> map((int)(number / 3), CreateThreeNode());

    if (number % 3 == 1)
        map.push_back(new Node(1));
    else if (number % 3 == 2)
        map.push_back(CreateTwoNode());

    return map;
}

void DeleteTree(Node* root) {
    if (root == nullptr) return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    delete root;
}

void WriteMap(Node* map, int* count, int* with, Counter* counter) {
    if (map->left == nullptr) return;
    WriteMap(map->left, count, with, counter);
    cout << map->data << ", " << *count << ", " << *with
        << ", " << counter->three<< ", " << counter->tow << ", " << counter->one << endl;
    if (map->data == 2)
        *with+=1;

    //*count += counter->GetCount();
}

int CountNumber(int number) {
    vector<Node*> map = CreateMap(number);
    int count = 1, with = 0;
    Counter counter{ 0, 0, number };

    for (auto node : map)
        WriteMap(node, &count, &with, &counter);
    

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