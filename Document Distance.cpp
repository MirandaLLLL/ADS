/*
Plagiarism is a form of academic dishonesty. To fight with such misconducts, plagiarism checkers are developed to compare any submitted article with all the articles stored in a database. The key is that given two documents, how to judge their similarity, or in other words, document distance? The document distance can be measured with their word metrics. In this project, you are supposed to write a program to calculate the distance of any given pair of documents.

Some important terms are defined as follows:

Word: is a continuous sequence of alphanumeric characters. For example, the phrase "the course data structure is fun" consists of 6 distinct words. Here we can assume that no word contains more than 20 characters.

Word frequency: denoted by F 
D
​
 (w) is the number of times the word w occurs in a document D.

Document distance metric: is defined to be the inner product of the two vectors containing the word frequencies for all words in two documents. Denote the frequency vector for document D 
i
​
  by  
F
 (D 
i
​
 )=(F 
i
​
 (w 
1
​
 ),⋯,F 
i
​
 (w 
n
​
 )) 
T
 , then the metric is given by ( 
F
 (D 
1
​
 ), 
F
 (D 
2
​
 ))=∑ 
i=1
n
​
 F 
1
​
 (w 
i
​
 )F 
2
​
 (w 
i
​
 ). In other words, the document distance metric is the projection of vector  
F
 (D 
1
​
 ) onto  
F
 (D 
2
​
 ), or vice versa.

Angle metric: is the angle between the vectors  
F
 (D 
1
​
 ) and  
F
 (D 
2
​
 ) which gives an indication of overlap between the two documents D 
1
​
  and D 
2
​
 . The angle can be computed by the following formula:

θ(D 
1
​
 ,D 
2
​
 )=arccos( 
∣∣ 
F
 (D 
1
​
 )∣∣⋅∣∣ 
F
 (D 
2
​
 )∣∣
( 
F
 (D 
1
​
 ), 
F
 (D 
2
​
 ))
​
 )

where θ∈[0,π/2] and ∣∣⋅∣∣ can be any norm of a vector. To be more specific, here we use the 2-norm which is defined by ∣∣ 
F
 (D)∣∣= 
( 
F
 (D), 
F
 (D))
​
 .

Input Specification:
Each input file contains one test case. For each case, the first line of input contains a positive integer N (≤100) which is the number of text files to be processed. Then N blocks follow, each contains a file. The first line of each file contains the title of the article (string of no more than 6 characters without any space), and the last line contains a single character #. After the file blocks, there is a line containing a positive integer M (≤100,000), followed by M lines of inquiries. Each inquiry gives a pair of file names separated by a space. The size of the largest test case is about 1 MB.

Output Specification:
For each inquiry, print in a line Case #: *, where # is the test case number starting from 1 and * is the document distance value accurate up to 3 decimal places.

Note: Your stemming algorithm must be able to handle "es", "ed", "ing", "ies" and must be case-insensitive. Stop words are not supposed to be ignored and must be treated as normal words.

Sample Input:
3
A00
A B C
#
A01
B C D
#
A02
A C
D A
#
2
A00 A01
A00 A02
Sample Output:
Case 1: 0.841
Case 2: 0.785
*/

#include<iostream>
#include<vector>
#include <iomanip>
#include<string>
#include<cmath>
#include <math.h>

using namespace std;
//vector<vector<int>> vec;
vector<string> dictionary;
int count_key = 0;

class block {
	friend istream& operator>>(istream&, block&);
public:
	string title;
	//vector<string> content;
	int key[10] = { 0 };
	int key_size;
};


istream& operator>>(istream& input, block& blo)  //overload cin;
{
	//blo.key[10] = {0};
	blo.key_size = 0;

	string tmp;
	int i;
	int judge;
	for (i = 0; i < 10; i++) {
		blo.key[i] = 0;
	}
	input >> blo.title;    // read the block's title;
	//input.ignore(1);                    //ignore "/"
	input >> tmp;
	while (tmp != "#") {
		blo.key_size++;
		judge = 0;
		//blo.content.push_back(tmp);  // read the block's content;
		for (i = 0; i < count_key; i++) {
			if (tmp == dictionary[i]) {
				blo.key[i]++;
				judge = 1;
			}
		}
		if (judge == 0) {
			dictionary.push_back(tmp);
			count_key++;
			blo.key[count_key - 1] = 1;
		}
		input >> tmp;
	}

	return input;
}


int N;
vector<block> doc;


float calculate_distance(string t1, string t2) {
	int i;
	int d1;
	int d2;
	for (i = 0; i < N; i++) {
		if (t1 == doc[i].title)
			d1 = i;
		if (t2 == doc[i].title)
			d2 = i;
	}//找到对应的文档

	float dis;
	float Numerator = 0;
	float Denominator1 = 0;
	float Denominator2 = 0;
	float max = doc[d1].key_size;

	if (doc[d2].key_size > max) {
		max = doc[d2].key_size;
	}

	for (i = 0; i < 10; i++) {
		Numerator = Numerator + doc[d2].key[i] * doc[d1].key[i];
		Denominator1 = Denominator1 + doc[d1].key[i] * doc[d1].key[i];
		Denominator2 = Denominator2 + doc[d2].key[i] * doc[d2].key[i];
	}
	float denominator = Denominator1 * Denominator2;
	denominator = pow(denominator, 0.5);
	dis = Numerator / denominator;
	//cout << Denominator1 << endl;
	//cout << Denominator2<<endl;
	//cout << Numerator<< endl;
	return acos(dis);
}

int main() {
	cin >> N;
	int i, j;
	block temp;
	for (i = 0; i < N; i++) {
		cin >> temp;
		doc.push_back(temp);
	}
	//cout << doc[0].key_size << ":"<<doc[0].key[0]<<endl;
	//cout << doc[1].key_size << ":" << doc[1].key[0] << ":" << doc[1].key[1] << endl;
	//cout << dictionary[0] << ";" << dictionary[1];
	//cout << doc[0].key[0] << endl;
	//cout << doc[1].key[0] << endl;

	int M;
	cin >> M;
	string tit1;
	string tit2;
	vector<float> f;
	float t;
	for (i = 1; i <= M; i++) {
		cin >> tit1;
		cin >> tit2;
		t = calculate_distance(tit1, tit2);
		cout << "Case " << i << ": " << setiosflags(ios::fixed) << setprecision(3) << t << endl;
	}

	return 0;
}

