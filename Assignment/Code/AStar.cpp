#include"AStar.h"

long double fact(long double num)/// generates the factorial of a given number
{
	long double rez = num;
	while (--num)
		rez *= num;
	return rez;
}

void AStar(ifstream& fin, ofstream& fout)
{
    map<long double, long double> costG;///the key represents the number and the value the cost to reach that  number
    set<tuple<long double, long double, string>> distF;///set that has as parameters
    ///the cost F, current number and operation to reach the current number
    map<pair<long double, string>, pair<long double, string>> prevNum;///map that stores
    ///the previous number from which the current one resulted
    stack<pair<long double, string>> sol;///stores each number in the path of the solution
    ///that has the smallest cost
    pair<long double,string> newNum[2];///used to create the next possible numbers
	long double initial, target, current, combinedCostF, solCost = LDBL_MAX;
	string operation;
    bool isOne = false;

    fin >> initial >> target;///read the initial number and the target number
    costG[initial] = 0;///initialize the cost G for the initial number to 0
	distF.insert(make_tuple( abs(initial - target), initial, "Initial" ));///inserts the initial number in the set
	prevNum[{initial, "Initial"}] = { 0,"\0" };///sets the previous number from the initial one to be 0

	next:
	while (!distF.empty())
	{
		auto it = distF.begin();///extracts the first number from the set
		tie(combinedCostF, current, operation) = *it;
		distF.erase(it);///removes the first number from the set

		if (current < 2 && isOne)///sees if the current number is <2 and if number 1 has already been processed
			goto next;///in case affirmative, skips to he next element in distF
		else
			if (current == 1)///if the current element is 1, mark it as processed
				isOne = true;

		if (current == target)/// checks if we reached the target
		{
			sol.push({ current, operation });
			while (prevNum[{current, operation}].second != "\0")/// inserts backwards every number
			{/// in the path till it reaches the first one
				auto aux = prevNum[{current, operation}];
				sol.push(aux);
				current = aux.first;
				operation = aux.second;
			}
			break;/// ends the algorithm at the first solution found, being the one with the lowest cost
		}

		newNum[0].first = sqrt(current);/// first possible operation that can be applied
		newNum[0].second = "Root";/// on any number is square root
		if (current != floor(current))/// checks if the current number is an integer
		{
			newNum[1].first = floor(current);/// if not, we can create a new integer number
			newNum[1].second = "Floor";/// using the floor operation
		}
		else/// if it is, we can create the factorial of the number
			if (current <= 1750)/// only if the resulting number will not exceed the
			{/// range of long double (approx 10^4920, and 1750! ~ 10^4917)
				newNum[1].first = fact(current);
				newNum[1].second = "Factorial";
			}
			else/// if it exceeds that range, we can not create a second number from the current one
				newNum[1].first = -1;
        for(int i = 0; i < 2; ++i)///tries to add a new path from the 2 newly created numbers
            if (newNum[i].first != -1 && costG.find(newNum[i].first) == costG.end())
            {
                long double costH = abs(target - newNum[i].first);/// the heuristic value is the difference between the new number and target
                costG[newNum[i].first] = costG[current] + abs(current - newNum[i].first);///the cost G of new number is the cost G of the current number plus
                ///the cost to reach the new number from the current number as an absolute difference between
                distF.insert(make_tuple( costG[newNum[i].first] + costH, newNum[i].first, newNum[i].second ));///adds the new possible path in the set distF,
                ///the first parameter costG[newNum[i].first] + costH representing the cost F = G + H, after which the set distF is sorted
                prevNum[newNum[i]] = { current, operation };/// adds as previous of the new number to be the current number
            }
	}
	if (!sol.empty())///if we have found a path, print it and its cost
        {
            fout<<"The path between "<< initial << " and " << target << " is:\n";
            while (!sol.empty())
            {
                fout<<setprecision(32) << sol.top().second << " " << sol.top().first << "\n";
                sol.pop();
            }
            fout << "\nThe path cost is: " << costG[target];
        }
        else///if not, write it was not found in long double range
            fout<<setprecision(32) << "\nCan not find a path between " << initial << " and " << target;
}
