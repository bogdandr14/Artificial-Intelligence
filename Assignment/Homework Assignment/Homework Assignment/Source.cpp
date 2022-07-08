#include<iostream>
#include<map>
#include<cmath>
#include<algorithm>
#include<math.h>
#include<float.h>
#include<stack>
#include<stdlib.h>
#include<set>
#include<iomanip>
using namespace std;
map<double, double> costG;
set<tuple<double, double, double, string>> distF;
map<pair<double,string>, pair<double,string>> prevNum;
stack<pair<double,string>> sol;
double target;
bool isOne = false;
double solCost = LDBL_MAX;
double fact(double num)
{
	double rez = num;
	while (--num)
		rez *= num;
	return rez;
}
bool AStar()
{
	double current, combinedCostF, prev;
	string operation;
	next:
	while (!distF.empty())
	{
		auto it = distF.begin();
		tie(combinedCostF, current, prev, operation) = *it;
		distF.erase(it);

		if (combinedCostF > solCost)
			break;

		if (current < 2 && isOne)
			goto next;
		else
			if (current == 1)
				isOne = true;

		if (current == target && solCost > costG[current])
		{
			solCost = costG[current];
			while(!sol.empty())
				sol.pop();
			sol.push({ current, operation });
			while (prevNum[{current, operation}].second != "\0")
			{
				auto aux = prevNum[{current, operation}];
				sol.push(aux);
				current = aux.first;
				operation = aux.second;
			}
		}
		pair<double,string> posib[2];
		posib[0].first = sqrt(current);
		posib[0].second = "Root";
		if (current != floor(current))
		{
			posib[1].first = floor(current);
			posib[1].second = "Floor";
		}
		else
			if (current <= 170)
			{
				posib[1].first = fact(current);
				posib[1].second = "Factorial";
			}
			else
				posib[1].first = -1;
	
		if ((costG.find(posib[0].first) == costG.end() || posib[0].first == target) && posib[0].first >1.41)
		{
			double costH = abs(target - posib[0].first);
			costG[posib[0].first] = costG[current] + abs(current - posib[0].first);
			distF.insert({ costG[posib[0].first] + costH, posib[0].first, current, posib[0].second });
			prevNum[posib[0]] = { current, operation };
		}

		if ((costG.find(posib[1].first) == costG.end() || posib[1].first == target) && posib[1].first != -1)
		{
			double costH = abs(target - posib[1].first);
			costG[posib[1].first] = costG[current] + abs(current - posib[1].first);
			distF.insert({ costG[posib[1].first] + costH, posib[1].first, current, posib[1].second });
			prevNum[posib[1]] = { current, operation };
		}
	}
	return !sol.empty();
}
int main()
{
	float initial;
	cin >> initial >> target;
	costG[initial] = 0;
	distF.insert({ abs(initial - target), initial, 0, "Initial" });
	prevNum[{initial, "Initial"}] = { 0,"\0" };

	if (AStar())
	{
		cout << "The cost is: " << solCost<< "\n\nThe path is:\n\n";
		while (!sol.empty())
		{
			cout << sol.top().second << " " << sol.top().first << "\n";
			sol.pop();
		}
	}
	else 
		cout << "Can not find a path between the given numbers";
	return 0;
}