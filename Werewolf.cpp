/*
not completely correct

7-1 Werewolf
分数 15
作者 陈越
单位 浙江大学
Werewolf（狼人杀） is a game in which the players are partitioned into two parties: the werewolves and the human beings. Suppose that in a game,

player #1 said: "Player #2 is a werewolf.";
player #2 said: "Player #3 is a human.";
player #3 said: "Player #4 is a werewolf.";
player #4 said: "Player #5 is a human."; and
player #5 said: "Player #4 is a human.".
Given that there were 2 werewolves among them, at least one but not all the werewolves were lying, and there were exactly 2 liers. Can you point out the werewolves?

Now you are asked to solve a harder vertion of this problem: given that there were N players, with M werewolves among them, at least one but not all the werewolves were lying, and there were exactly L liers. You are supposed to point out the werewolves.

Input Specification:
Each input file contains one test case. For each case, the first line gives three positive integer N (5 ≤ N ≤ 100), M and L (2 ≤ M，L < N). Then N lines follow and the i-th line gives the statement of the i-th player (1 ≤ i ≤ N), which is represented by the index of the player with a positive sign for a human and a negative sign for a werewolf.

Output Specification:
If a solution exists, print in a line in descending order the indices of the M werewolves. The numbers must be separated by exactly one space with no extra spaces at the beginning or the end of the line. If there are more than one solution, you must output the largest solution sequence -- that is, for two sequences A = { a[1], ..., a[M] } and B = { b[1], ..., b[M] }, if there exists 0 ≤ k < M such that a[i] = b[i] (i ≤ k) and a[k+1]>b[k+1], then A is said to be larger than B. In case there is no solution, simply print No Solution.

Sample Input 1:
5 2 2
-2
+3
-4
+5
+4
Sample Output 1:
4 1
Sample Input 2:
6 2 3
-2
+3
-4
+5
+4
-3
Sample Output 2:
6 4
Sample Input 3:
6 2 5
-2
+3
-4
+5
+4
+6
Sample Output 3:
No Solution
*/

#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;
int N;
int M;
int L;


int player[100];
int result=0 ;
vector<int> werewolves; //store the players's indexes who are wolves;

void judge(int index) {
	
	if (werewolves.size() == M) {// when the werewolves are full
		//for (int i = 0; i < M; i++)
			//cout << werewolves[i]<<"  ";
		//cout << endl;
		int Currentliars = 0; //count the current number of lying players;
		int Wereliars = 0; //count the number of lying wolves;

		for (int i = 1; i <= N; i++) {
			vector<int>::iterator r1 = find(werewolves.begin(), werewolves.end(), abs(player[i]));
			vector<int>::iterator r2 = find(werewolves.begin(), werewolves.end(), abs(i));
			if (((player[i] < 0) && (r1 == werewolves.end())) || ((player[i] > 0) && (r1 != werewolves.end()))) {//when this player lies
				Currentliars++;
				if (r2 != werewolves.end()) {//when the liar is a werewolf
					Wereliars++;
				}
			}
		}
		//cout << "Currentliars:" << Currentliars << ";" << "Wereliers:" << Wereliars<<endl;
		if (Currentliars == L && Wereliars >= 1 && Wereliars < M)//if meeting the requirement
		{
			result = 1;
		}
		return;
	}
	if (index == 0) {
		return;
	}

	werewolves.push_back(index);//assume this player  is werewolf
	judge(index - 1);
	if (result == 1)//if it meet the requirement
	{
		return;
	}
	werewolves.pop_back();//find out this player is not the werewolf
	judge(index - 1);
}

int main() {
	cin >> N;
	cin >> M;
	cin >> L;
	int i;
	for (i = 1; i <= N; i++) {
		cin >> player[i];
	}

	//werewolves.push_back(6);
	//werewolves.push_back(4);
	/*int Currentliars = 0; //count the current number of lying players;
	int Wereliars = 0; //count the number of lying wolves;
	//i = 5;
	
	for (int i = 1; i <= N; i++) {
		vector<int>::iterator r1 = find(werewolves.begin(), werewolves.end(), abs(player[i]));
		vector<int>::iterator r2 = find(werewolves.begin(), werewolves.end(), abs(i));
		if (((player[i] < 0) && (r1 == werewolves.end())) || ((player[i] > 0) && (r1 != werewolves.end()))) {//当前遍历到的玩家在撒谎
			Currentliars++;
			if (r2 != werewolves.end()) {//when the liar is a werewolf
				Wereliars++;
			}
		}
	}

	if (Currentliars == L && Wereliars >= 1 && Wereliars < M)//满足题设条件，f设为true
	{
		result = 1;
	}
	cout <<Currentliars<<"   "<< Wereliars;*/

	/*int Currentliars = 0; //count the current number of lying players;
	int Wereliars = 0; //count the number of lying wolves;

	for (int i = 1; i <= N; i++) {
		vector<int>::iterator r1 = find(werewolves.begin(), werewolves.end(), abs(player[i]));
		vector<int>::iterator r2 = find(werewolves.begin(), werewolves.end(), abs(i));
		if (((player[i] < 0) && (r1 == werewolves.end())) || ((player[i] > 0) && (r1 != werewolves.end()))) {//当前遍历到的玩家在撒谎
			Currentliars++;
			if (r2 != werewolves.end()) {//when the liar is a werewolf
				Wereliars++;
			}
		}
	}

	if (Currentliars == L && Wereliars >= 1 && Wereliars < M)//满足题设条件，f设为true
	{
		result = 1;
	}

	cout << result; */
	judge(N);

	if (result == 0) {
		cout << "No Solution";
	}
	else {
		for (i = 0; i < (M - 1); i++) {
			cout << werewolves[i] << " ";
		}
		cout << werewolves[M - 1];
	}
	
	return 0;
}
