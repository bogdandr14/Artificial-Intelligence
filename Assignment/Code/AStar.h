#include<fstream>
#include<math.h>
#include<float.h>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#include<iomanip>
#include<tuple>
using namespace std;


///This function is used to generate the factorial of a given number
///@param num - long double
long double fact(long double num);


///This function is used to find, for each input test, a way to transform
///a number into another one using only factorials, square roots and floors,
///and represents my own implementation of A* Search algorithm
///@param fin - ifstrean&
///@param fout - ofstream&
void AStar(ifstream& fin, ofstream& fout);
