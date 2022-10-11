
/*With highways available, driving a car from Hangzhou to any other city is easy. But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. Different gas station may give different price. You are asked to carefully design the cheapest route to go.

Input Specification:
Each input file contains one test case. For each case, the first line contains 4 positive numbers: C 
max
​
  (≤ 100), the maximum capacity of the tank; D (≤30000), the distance between Hangzhou and the destination city; D 
avg
​
  (≤20), the average distance per unit gas that the car can run; and N (≤ 500), the total number of gas stations. Then N lines follow, each contains a pair of non-negative numbers: P 
i
​
 , the unit gas price, and D 
i
​
  (≤D), the distance between this station and Hangzhou, for i=1,⋯,N. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the cheapest price in a line, accurate up to 2 decimal places. It is assumed that the tank is empty at the beginning. If it is impossible to reach the destination, print The maximum travel distance = X where X is the maximum possible distance the car can run, accurate up to 2 decimal places.

Sample Input 1:
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
Sample Output 1:
749.17
Sample Input 2:
50 1300 12 2
7.10 0
7.00 600
Sample Output 2:
The maximum travel distance = 1200.00
*/

#include<iostream>
#include<string>
#include<vector>
#include <iomanip>

using namespace std;

class gas_station {
public:
	float P;
	float D;

};



int main()
{
	float Cmax;
	float D_tot;
	float D_avg;
	int N;	
	cin >> Cmax >> D_tot >> D_avg >> N;
	int i;
	gas_station stations[10000];
	float price;
	float distance;

	for (i = 0; i < N; i++) {
		cin >> price >> distance;
		stations[i].P = price;
		stations[i].D = distance;
	}
		
	stations[N].P= 0;
	stations[N].D = D_tot;
	float tmp_P;
	float tmp_D;
	int j;
	for (i = 0; i < N;i++) {
		for (j = i+1; j <= N; j++) {
			if (stations[i].D > stations[j].D) {
				tmp_P = stations[i].P;
				tmp_D = stations[i].D;
				stations[i].P = stations[j].P;
				stations[i].D = stations[j].D; 
				stations[j].P = tmp_P;
				stations[j].D = tmp_D;
				
			}
		}

	}//排序


	if (stations[0].D != 0) 
		cout << "The maximum travel distance = 0.00";
	else
	{
		int Cur_stat = 0;
		float Cur_cost = 0;
		float Cur_tank = 0;
		float Max_dis = Cmax * D_avg;

		int Min_stat;
			float Cur_min;

			while (Cur_stat < N)
			{
				int Min_stat = Cur_stat + 1;//最小价格的站
				float Cur_min = stations[Cur_stat + 1].P;//最小的价格
				if ((stations[Min_stat].D - stations[Cur_stat].D) <= Max_dis) {
					for (int i = Cur_stat + 1; i <= N && (stations[i].D - stations[Cur_stat].D) <= Max_dis; i++)//在续航里程内检索加油站 
					{
						if (stations[i].P <= Cur_min)
						{
							Cur_min = stations[i].P;
							Min_stat = i;
							if (Cur_min < stations[Cur_stat].P) {
								break;
							}
						}
					}
					float tank_need = (stations[Min_stat].D - stations[Cur_stat].D) / D_avg;
					if (Cur_min < stations[Cur_stat].P)
					{
						if (Cur_tank < tank_need)
						{
							Cur_cost = Cur_cost + (tank_need - Cur_tank) * stations[Cur_stat].P;
							Cur_tank = 0;
						}
						else
							Cur_tank = Cur_tank - tank_need;
					}
					else
					{
						Cur_cost = Cur_cost + (Cmax - Cur_tank) * stations[Cur_stat].P;
						Cur_tank = Cmax - tank_need;
					}
					Cur_stat = Min_stat;
				}
				else
				{
					break;
				}
			}
		if (Cur_stat == N) {
			cout.setf(ios::fixed);
			cout << fixed << setprecision(2) << Cur_cost << endl;
		}
		else {
			cout.setf(ios::fixed);
			cout<<"The maximum travel distance = "<< fixed << setprecision(2) <<  stations[Cur_stat].D + Max_dis<<endl;

		}
	}
	return 0;
}


