#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

bool IsSame(int a, int b, int c) {
	return a == b || b == c || a == b;
}

struct State {
	int number1 = 0;
	int number2 = 0;
	int number3 = 0;
	State(int a, int b, int c) : number1(a), number2(b), number3(c)
	{
		if (IsSame(a, b, c))
			throw invalid_argument("같은 숫자가 존재합니다.");
	}
	//vector<int> state;
	//State(int a, int b, int c) : state{ a, b, c }
	//{
	//	if (IsSame(a, b, c))
	//		throw invalid_argument("같은 숫자가 존재합니다.");
	//}
};

#pragma region State관련 Method 정의
bool Exist(State input, int find) {
	return input.number1 == find || input.number2 == find || input.number3 == find;
}
void Remove_State(vector<State>& input, const State& remove) {
	//auto it = find(input.begin(), input.end(), remove);
	auto its = remove_if(input.begin(), input.end(), [&](const State& state) {
		return state.number1 == remove.number1 && state.number2 == remove.number2 && state.number3 == remove.number3;
		});
	if (its != input.end())
		input.erase(its);
}
#pragma endregion

struct Answer {
	int strike = 0;
	int ball = 0;
	Answer(int strike, int ball) : strike(strike), ball(ball) {}
};

int count_Bool(bool input1, bool input2, bool input3, bool find)
{
	int count = 0;
	if (input1 == find)
		count++;
	if (input2 == find)
		count++;
	if (input3 == find)
		count++;
	return count;
}

#pragma region T 관련 Method 정의
vector<State> Initialize_T() {
	vector<State> t = {};
	for (int a = 1; a < 10; a++)
		for (int b = 1; b < 10; b++)
		{
			if (a == b)
				continue;

			for (int c = 1; c < 10; c++)
			{
				if (b == c || a == c)
					continue;
				t.push_back(State(a, b, c));
			}
 		}
	return t;
}
#pragma endregion

#pragma region Caculate BaseBall
void Action(vector<State>& t, State question, Answer answer) {
	if (answer.strike == 3)
		t = vector<State> { question };
	else {
		Remove_State(t, question);
		for (int index = 0; index < (int)(t.size()); index++)
		{
			State& state = t[index];
			int strike = count_Bool(state.number1 == question.number1, state.number2 == question.number2, state.number3 == question.number3, true);
			if (strike != answer.strike)
			{
				Remove_State(t, state);
				index--;
			}
			else {
				int ball = count_Bool(Exist(state, question.number1), Exist(state, question.number2), Exist(state, question.number3), true) - strike;
				if (ball != answer.ball)
				{
					Remove_State(t, state);
					index--;
				}
			}
		}
	}
}
#pragma endregion

int main()
{
	int repeat;
	cin >> repeat;

	vector<State> questions = {};
	vector<Answer> answers = {};
	for (int index = 0; index < repeat; index++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		int number1 = (int)(a / 100);
		int number2 = (int)((a - number1 * 100) / 10);
		int number3 = (int)(a - number1 * 100 - number2 * 10);
		questions.push_back(State(number1, number2, number3));
		answers.push_back(Answer(b, c));
	}

	vector<State> T = Initialize_T();
	for(int index = 0; index < repeat; index++)
		Action(T, questions[index], answers[index]);

	cout << T.size() << endl;

	return 0;
}