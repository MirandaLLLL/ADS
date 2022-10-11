#include<iostream>
#include<string>
#include<ctime>
#include<time.h>
using namespace std;
#define MAXSIZE 10001

// The definition of huffmantreenode
typedef struct HuffmanTreeNode {
    int weight;
    char ch;
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
}HuffmanTreeNode;

// The definition of minheapnode
typedef struct HeapNode {
    HuffmanTreeNode* data;
    int size;
    int capacity;
}*MinHeap;

MinHeap CreatMinHeap(int MaxSize);
HuffmanTreeNode* Deletemin(MinHeap p);
HuffmanTreeNode* CreateHuffmanTree(MinHeap p);
void Insert2Heap(MinHeap pHeap, HuffmanTreeNode HTnode);
int getWPL(HuffmanTreeNode*p,int depth);
bool Isprefix(string* tmpstrs, int n);
bool Isprefix2(string* tmpStrs, int n);
void print_huffman(HuffmanTreeNode* huffman);

int huff_code[63];
int huff_i = 0;
char* character;
int* char_huff[63];
int char_length[63];

int main() {
    int num_code, num_student;
    char tmpChar;
    int tmpWeight;
    int WPL;
    clock_t startTime, endTime, total_start, total_end;
    
    // total_start = clock(); // The start clock for total time
    cin >> num_code;
    
    // startTime = clock(); // The start clock to create the Huffman Tree
    MinHeap pMinheap = CreatMinHeap(num_code);
    int* weight = new int[num_code];
    character = new char[num_code];
    for(int i=0; i<num_code; i++)
        char_huff[i] = new int[63];
    for (int i = 0;i < num_code;i++) {
        cin >> tmpChar >> tmpWeight;
        weight[i] = tmpWeight;
        character[i] = tmpChar;
        HuffmanTreeNode tmpInsert;
        tmpInsert = { tmpWeight,tmpChar,NULL,NULL };
        Insert2Heap(pMinheap, tmpInsert);
    }
    HuffmanTreeNode* HuffmanT = CreateHuffmanTree(pMinheap);
    // endTime = clock(); // The end clock to create the Huffman Tree
    // cout << "The run time of creating Huffman Tree is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    //startTime = clock(); // The start clock to calculate WPL
    WPL = getWPL(HuffmanT, 0);
    // endTime = clock(); // The end clock to calculate WPL
    // cout << "The run time of calculating WPL is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    // Print the Huffman tree

	/*print_huffman(HuffmanT);         
    for(int i=0; i<num_code; i++){
        printf("%c ", character[i]);
        int j=0;
        for(j; j<char_length[i]; j++)
            printf("%d", char_huff[i][j]);
        printf("\n");
    }*/
    
	// Verify students' Huffman code
    cin >> num_student;
    string* tmpStrs = new string[num_code];
    int stu_WPL;
    for (int i = 0;i < num_student;i++) {
        stu_WPL = 0;
        // startTime = clock(); // The start clock to calculate students' WPL 
		// Calculate the student's Huffmancode's WPL
        for (int j = 0;j < num_code;j++) {
            cin >> tmpChar >> tmpStrs[j];
            stu_WPL += weight[j] * tmpStrs[j].length();
        }
        // endTime = clock(); // The end clock to calculate students' WPL
        // cout << "The run time of calculating tests' WPL is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

        // Judgment 1: Whether the WPL minimum is met
        if (stu_WPL != WPL) cout << "No" << endl;

        // Judgment 2: Whether prefix-free coding is satisfied.
		//             In our program, we did this in two ways.
        else {
            //startTime = clock(); // The start clock to judge the prefixion of huffman code

			// Method 1: Implemented by judging the string
            // bool flag = Isprefix(tmpStrs, num_code);

			// Method 2: Implemented by Trie
            bool flag = Isprefix2(tmpStrs, num_code);
            // endTime = clock();// The end clock to judge the prefixion of huffman code
            // cout << "The run time of judging is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            
            if (flag) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    //total_end = clock();
    //cout << "The total run time is: " <<(double)(total_end - total_start) / CLOCKS_PER_SEC << "s" << endl;
}

// Initialize to create the minimum heap
MinHeap CreatMinHeap(int MaxSize) {
    MinHeap mHeap = (MinHeap)malloc(sizeof(struct HeapNode));
    mHeap->data = (HuffmanTreeNode *)malloc((MaxSize + 1) * sizeof(struct HuffmanTreeNode));
    mHeap->size = 0;
    mHeap->capacity = MaxSize;
    mHeap->data[0].weight = -1;
    
    return mHeap;
}

// Insert to MinHeap
void Insert2Heap(MinHeap pHeap, HuffmanTreeNode HTnode) {
    if (pHeap->size == pHeap->capacity) {
        cout<<"Minheap is full!"<<endl;
        return;
    }
    int i = ++pHeap->size;
	// Find the place to insert
    for (; pHeap->data[i / 2].weight > HTnode.weight; i /= 2)
    {
        pHeap->data[i] = pHeap->data[i / 2];
    }
    pHeap->data[i] = HTnode;
}

// Delete minimum value in the heap and also maintain the structure
HuffmanTreeNode* Deletemin(MinHeap pHeap) {
    int parent, child;
    HuffmanTreeNode *MinNode,tmp;
    MinNode = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));

	// Find the minimum node
    *MinNode = pHeap->data[1];
    tmp = pHeap->data[pHeap->size--];
    for (parent = 1;parent * 2 <= pHeap->size;parent = child) {
        child = parent * 2;
        if ((child != pHeap->size) && (pHeap->data[child].weight > pHeap->data[child + 1].weight)) child++;
        if (pHeap->data[child].weight >= tmp.weight)
        {
            break;
        }
        else {
            pHeap->data[parent] = pHeap->data[child];
        }
    }
    pHeap->data[parent] = tmp;
    return MinNode;
}

// Create the HuffmanTree
HuffmanTreeNode* CreateHuffmanTree(MinHeap pHeap) {
    HuffmanTreeNode* T;
    int j = pHeap->size;
    for (int i = 1;i < j;i++) {
        T = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
		// Delete root from min heap and attach it to left child of node
        T->left = Deletemin(pHeap);
		// Delete root from min heap and attach it to right child of node
        T->right = Deletemin(pHeap);
		// Calculate the weight of this node
        T->weight = T->left->weight + T->right->weight;
		// Insert the new weight into the min heap 
        Insert2Heap(pHeap, *T);
    }
    T = Deletemin(pHeap);
    return T;
}
// Calculate the WPL
int getWPL(HuffmanTreeNode*p, int depth) {
    if (!p->left && !p->right) {
        return (depth * p->weight);
    }
    else {
        return (getWPL(p->left, depth + 1) + getWPL(p->right, depth + 1));
    }
}
// Judging whether has prefix code. 
// Method 1: Implemented by judging the string
bool Isprefix(string* tmpStrs,int n) {
    for (int i = 0;i < n;i++) {
        int c_len = tmpStrs[i].length();
        for (int j = 0;j < n;j++) {
            if (i == j) continue;
            int l_len = tmpStrs[j].length();
            if (c_len <= l_len && tmpStrs[i] == tmpStrs[j].substr(0, c_len)) {
                return false;
            }
        }
    }
    return true;
}

// Judging whether has prefix code. 
// Method 2: Implemented by Trie
bool Isprefix2(string* tmpStrs, int n) {
    HuffmanTreeNode *Tree, *p;
    Tree = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
    int flag = 0;
    Tree->right = NULL;
    Tree->left = NULL;
    Tree->weight = 0;
    for (int i = 0;i < n;i++) {
        string c_str = tmpStrs[i];
        int c_len = c_str.length();
        p = Tree;
        for (int j = 0;j < c_len;j++) {
			// If the code is '1', we store it in the left node
            if (c_str[j] == '1') {
                if (p->left == NULL) {
                    p->left = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
                    p = p->left;
                    p->left = NULL;
                    p->right = NULL;
					// Mark the end of the code with '1'
                    if (j == c_len - 1) p->weight = 1;
                    else p->weight = 0;
                }
                else {
					// Find the prefix part 
                    if (p->left->weight == 1 || j == c_len - 1) {
                        flag = 1;
                        break;
                    }
                    else {
                        p = p->left;
                    }
                }
            }
			// If the code is '0', we store it in the right node
            else {
                if (p->right == NULL) {
                    p->right = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
                    p = p->right;
                    p->left = NULL;
                    p->right = NULL;
					// Mark the end of the code with '1'
                    if (j == c_len - 1) p->weight = 1;
                    else p->weight = 0;
                }
                else {
					// Find the prefix part 
                    if (p->right->weight == 1 || j == c_len - 1) {
                        flag = 1;
                        break;
                    }
                    else {
                        p = p->right;
                    }
                }
            }
            if (flag == 1) break;
        }
        if (flag == 1) break;
    }
    return !flag;
}

// Test: Print the Huffmantree created by the program
void print_huffman(HuffmanTreeNode* huffman) {
	if (huffman != NULL && !((huffman->ch > 47 && huffman->ch < 58) || (huffman->ch > 64 && huffman->ch < 91) || (huffman->ch > 96 && huffman->ch < 123) || huffman->ch == 95)) {
		huff_code[huff_i++] = 0;
		print_huffman(huffman->left);
		huff_i--;
		huff_code[huff_i++] = 1;
		print_huffman(huffman->right);
		huff_i--;
	}
	else {
		for (int i = 0; i < 63; i++) {
			if (character[i] == huffman->ch) {
				for (int j = 0; j < huff_i; j++)
					char_huff[i][j] = huff_code[j];
				char_length[i] = huff_i;
			}
		}
		return;
	}
}

