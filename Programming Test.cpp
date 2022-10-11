
/*
function

Bob will participate in a programming contest. There are altogether n problems in the contest. Unlike in PAT (Programming Ability Test), in a programming contest one can not obtain partial scores. For problem i, Bob will need time[i] to solve it and obtains the corresponding score[i], or he may choose not to solve it at all. Bob will be happy when he obtains a total score no less than happy_score. You are supposed to find the minimum time needed for Bob to be happy. The function need_time must return the minimum time, or -1 if it is impossible for Bob to obtain a score no less than happy_score.

Format of function:
int need_time(const int time[], const int score[], int happy_score, int n);
Here n (1≤n≤ MAXN) is the number of problems;
happy_score (1≤ happy_score ≤ MAXS) is the minimum score for Bob to be happy;
time[] is the array to store time[i] (1≤time[i]≤100) which is the time to solve problem i;
score[] is the array to store score[i] (1≤score[i]≤100) which is the score Bob gets for solving problem i.

Sample program of judge:
#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

/* Your function will be put here */
Sample Input:
6 121

84 87 78 16 94 38
87 93 50 22 63 28
Sample Output:
125
*/


int Max(int a, int b)  //return the max value
{
    if (a > b)
        return a;
    else
        return b;
}

int Min(int a, int b) //return the min value
{
    if (a > b)
        return b;
    else
        return a;
}

int need_time(const int time[], const int score[], int happy_score, int n) {
  // int current_min=score[0];
    int i,j;
    int total_score = 0;
    int total_time = 0;

    //Calculate the total score and total time when finishing all the problems
    //find the minimum score of a single problem;
    for (i = 0; i < n; i++) {
    //    current_min = Min(score[i], current_min);
        total_score = total_score+score[i];
        total_time= total_time+time[i];
    }
    
    int package_size = total_score - happy_score;

    if (package_size<0)
     return -1;
    else {
        int Maximum_time[package_size+1][n+1];//Maximum_value[i][j]：Maximum time when remaining i size package and j problems can be put into;
        for (i = 0; i <= package_size; i++) {
            for (j = 0; j <= n; j++) {
                Maximum_time[i][j] = 0;
            }
        }
        for (i = 0; i <= package_size; i++) {
            for (j = 0; j < n; j++){
                if (i >= score[j])  //The remaining package size is able to contain the jth problem,choose the larger time
                    Maximum_time[i][j + 1] = Max(Maximum_time[i][j], time[j] + Maximum_time[i - score[j]][j]);
                else
                    Maximum_time[i][j + 1] = Maximum_time[i][j];
            }
        }
     int min_time=total_time - Maximum_time[package_size][n];
        if (min_time>0)
            return min_time;
        else
             return -1;
    }
}
