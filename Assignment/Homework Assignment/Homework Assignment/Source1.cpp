#include<iostream>
#include<map>
#include<cmath>
#include<algorithm>
#include<math.h>
#include<stack>
#include<iomanip>
using namespace std;
map<double, double> costG;
stack<double> sol;
float target;
bool smallOne;
double fact(double num)
{
	double rez = num;
	for (double i = 2; i < num; ++i)
		rez *= i;
	return rez;
}
bool DFS(double current)
{
	if (current == target)
	{
		cout << "The cost is: " << costG[current];
		return true;
	}
	double posib[2];
	posib[0] = sqrt(current);
	if (current == floor(current))
		if (current <= 170)
			posib[1] = fact(current);
		else
			posib[1] = -1;
	else
		posib[1] = floor(current);
	if (costG.find(posib[0]) != costG.end())
	{
		costG[posib[0]] = min(costG[posib[0]], costG[current] + abs(current - posib[0]));
		posib[0] = -1;
	}
	else
		costG[posib[0]] = costG[current] + abs(current - posib[0]);
	if (costG.find(posib[1]) != costG.end() && posib[1] != -1)
	{
		costG[posib[1]] = min(costG[posib[1]], costG[current] + abs(current - posib[1]));
		posib[1] = -1;
	}
	else
		if (posib[1] != -1)
			costG[posib[1]] = costG[current] + abs(current - posib[1]);
	if (posib[1] != -1 && posib[0] != -1)
	{
		if (costG[posib[0]] + abs(target - posib[0]) > costG[posib[1]] + abs(target - posib[1]))
			swap(posib[0], posib[1]);
	}if (posib[0] == -1)
		swap(posib[0], posib[1]);
	if (posib[0] != -1)
		if (DFS(posib[0]))
		{
			sol.push(posib[0]);
			return true;
		}
		else
			if (posib[1] != -1)
				if (DFS(posib[1]))
				{
					sol.push(posib[1]);
					return true;
				}
				else
					return false;
			else
				return false;
	else
		return false;

}
int main()
{
	float initial;
	cin >> initial >> target;
	costG[initial] = 0;
	if (DFS(initial))
	{
		cout << "\nPath size: " << sol.size();
		cout << "\nThe path is:\n" << initial << "\n";
		while (!sol.empty())
		{
			cout << sol.top() << "\n";
			sol.pop();
		}
	}
	for (auto it : costG)
	{
		if (it.first < 2.0 && smallOne)
			continue;

		cout << setprecision(20) << "\n" << it.first;
		if (it.first < 2.0)
			smallOne = true;
	}

	return 0;
}