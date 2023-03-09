//Consider the situation that Mr.Smith climbs up stairs.
//He can climb 1 step or 2 steps at one time.
//It costs him 1 calory for climbing 1 step, 
//and 3 calories for climbing 2 steps at one time.
//Q1: Now Mr.Smith needs to climb m steps and he only has n calories.
//How many ways are there for him to climb m steps ?
//Q2: After eating too much, Mr.Smith decides to climb m steps for losing weight.
//Now he also has n calories left.
//At this time, he wants to consume as much calories as possible 
//but no more than n calories.
//How many ways are there for him to climb m steps ?

#include <iostream>
using namespace std;

int caculateC(int bottom, int upper)		//caculate the permutation
{
	int demoninator = 1, numerator = 1;		//divide to caculate
	for (int i = bottom; i >= upper; i--)	//caculation of demonitator
	{
		demoninator *= i;
	}
	for (int j = 1; j <= upper; j++)		//caculation of numerator
	{
		numerator *= j;
	}
	return demoninator / numerator;			//give out the result
}

int main()
{
	int m, n;			//define 2 nums
	cin >> m >> n;		//cin 2 nums

	if (cin.fail() || m <= 0 || n <= 0 || m > n)	//error detection
	{
		cout << "0";
		return 0;
	}

	int cnt1 = m;		//num of 1 step
	int cnt2 = 0;		//num of 2 steps
	while (m >= 0 && n >= cnt2 * 3 + m)		//enough steps and calories
	{
		m -= 2;			//to count the num of 2 steps
		n -= 3;
		cnt2++;
	}
	cnt1 = cnt1 - 2 * cnt2;		//the num of 1 step

	cout << caculateC(cnt1 + cnt2, cnt2) << endl;	//permutation

	return 0;
}