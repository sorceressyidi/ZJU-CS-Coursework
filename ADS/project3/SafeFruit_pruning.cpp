/*
 *  Project name:       Safe fruit
 *  Date:               2020/4/2
 *  Author:             
 */

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MaxM = 110;                   //max number of fruit
const int inf = 10000;
const int Round = 1000;

typedef struct fruitnode* Fruit;
struct fruitnode {
    int index;
    Fruit next;
};

typedef struct fruitlist* FruitList;
struct fruitlist {
    Fruit fruits[MaxM];
};

       
bool choose[MaxM] = { false };              //the fruit we choose to be the safe fruit
bool result[MaxM] = { false };              //the fruit we choose to be the safe fruit as result
bool conflict[MaxM] = { false };            //the conflicting fruit which we will never choose
bool istrue[MaxM] = { false };
bool checkmin = false;						//check if the output is unique
bool checkcopy = false;						//check if the number copied are not the same
int prices[MaxM] = { 0 };                   //input price for each fruit
int Maxnumber = 0, minprice = inf;
int N, M;                                   //input integer N as tips number & M as fruit number.   

int read();
void Print();
void Copy();
void Check();
void Backtracking(int index, int number, FruitList L);
FruitList BuildFruitList();
void InitialChoose(FruitList L);

/*
 *  Function:       Print()
 *  Usage:          void Print()
 *  ---------------------------------------------
 *  This function output the final answer to standard output.
 *  The answer contains
 *      1. the maximum number of safe fruits.
 *      2. all the safe fruits, in increasing order of their ID's.
 *      3. total price of the above fruits.
 */
void Print() {
	if(checkmin){
		cout << "The output is not unique!" << endl; //state the error if the output is not unique
		return;
	}
    bool first = true;
    cout << Maxnumber << endl;
    for (int i = 1; i <= M; i++) {
        if (result[i]) {
            if (first) {
                cout << setfill('0') << setw(3) << i;
                first = false;
            }
            else
                cout << ' ' << setfill('0') << setw(3) << i;
        }
    }
    cout << endl << minprice << endl;
}

/*
 *  Function:       Copy()
 *  Usage:          void Copy()
 *  ---------------------------------------------
 *  This function will store the result of chosen fruit to the array 'result' if it's better.
 */
void Copy() {
	checkcopy = false;
    for (int i = 1; i <= M; i++) {
        result[i] = choose[i];
        if(result[i] != choose[i])checkcopy = true; //if the result is different
    }
}

/*
 *  Function:       Check()
 *  Usage:          void Check()
 *  ---------------------------------------------
 *  This function check whether if the new list of safe fruit is better than the old one,
 *  if so, keep it.
 */
void Check() {
    int number = 0, totalprice = 0;
    for (int i = 1; i <= M; i++) {
        if (choose[i]) {
            number++;
            totalprice += prices[i];
        }
    }
    if (number > Maxnumber) {
        Maxnumber = number;
        minprice = totalprice;
        Copy();
    }
    else if (number == Maxnumber) {
        if (totalprice <= minprice) {
            Maxnumber = number;
            minprice = totalprice;
            Copy();
            if(totalprice == minprice && checkcopy) checkmin = true; //if the output is not unique
        	else checkmin = false; //if the output is unique
        }
    }
}

/*
 *  Function:       Backtracking()
 *  Usage:          void Backtracking(int index)
 *  ---------------------------------------------
 *  This function do the backtracking algorithm.
 */
void Backtracking(int index, int number, FruitList L) {
    bool findnext = false;

    if (choose[index] == true) {
        for (int i = index + 1; i <= M; i++) {
            if (M - i + 1 + number < Maxnumber)        break;       //first method of pruning
            if (conflict[i] != true) {
                findnext = true;
                Backtracking(i, number + 1, L);                        //backtracking to the next node in order.
            }
        }
        if (findnext == false)    Check();               //if this is the last node, check whether if this is a better result.
        return;
    }
    choose[index] = true;                           //push this fruit into the safe fruit list
    for (Fruit p = L->fruits[index]->next; p != NULL; p = p->next) {
        if (conflict[p->index])  istrue[p->index] = true;
        conflict[p->index] = true;
    }
    findnext = false;

    for (int i = index + 1; i <= M; i++) {
        if (M - i + 1 + number < Maxnumber)        break;       //first method of pruning
        if (conflict[i] != true) {
            findnext = true;
            Backtracking(i, number + 1, L);                        //backtracking to the next node in order.
        }
    }

    if (findnext == false)    Check();               //if this is the last node, check whether if this is a better result.

    choose[index] = false;                          //delete this fruit from the safe fruit list
    for (Fruit p = L->fruits[index]->next; p != NULL; p = p->next) {
        if (istrue[p->index]) {
            istrue[p->index] = false;
            continue;
        }
        conflict[p->index] = false;                 //free the conflicting node
    }

    findnext = false;

    for (int i = index + 1; i <= M; i++) {
        if (M - i + 1 + number < Maxnumber)        break;           //first method of pruning
        if (conflict[i] == false) {
        	findnext = true;
            Backtracking(i, number, L);                        //backtracking to the next node in order.
        }
    }

    if (findnext == false)    Check();               //if this is the last node, check whether if this is a better result.

}

/*
 *  Function:       BuildFruitList()
 *  Usage:          FruitList BuildFruitList()
 *  ---------------------------------------------
 *  This function build a fruit list.
 */
FruitList BuildFruitList() {
    int n1, n2;

    //a strct contain all the fruit
    FruitList L = (FruitList)malloc(sizeof(struct fruitlist));
    for (int i = 1; i <= M; i++) {
        L->fruits[i] = (Fruit)malloc(sizeof(struct fruitnode));
        L->fruits[i]->next = NULL;
    }

    //built the confliction between different fruits
    for (int i = 0; i < N; i++) {
		n1 = read();
		n2 = read();
        Fruit p1 = (Fruit)malloc(sizeof(struct fruitnode));
        Fruit p2 = (Fruit)malloc(sizeof(struct fruitnode));
        p1->index = n1;
        p2->index = n2;
        p1->next = L->fruits[n2]->next;
        L->fruits[n2]->next = p1;
        p2->next = L->fruits[n1]->next;
        L->fruits[n1]->next = p2;
    }

    return L;
}

/*
 *  Function:       InitialChoose()
 *  Usage:          void InitialChoose(FruitList L)
 *  ---------------------------------------------
 *  This function initial the choose array, if the fruit have no conflicting fruit
 *  put it into the final result and never check it.
 */
void InitialChoose(FruitList L) {
    for (int i = 1; i <= M; i++) {
        if (L->fruits[i]->next == NULL) {
            choose[i] = true;
        }
    }
}

/*
 * Function: read
 * Usage: read();
 * --------------------------------------------------------------
 * This function reads in a number of unknown length.
 */
int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main()
{
    int i,x,y,num,id,price;
	char input[30];
    printf("Input case number:\n");
    scanf("%d", &num);
    sprintf(input, "testdata/input%d.txt", num);
    freopen(input, "r", stdin);
    // Read in the header (N,M) of the file: -----------------------
    scanf("%d%d\n", &N, &M);
    printf("N = %d, M = %d\n\n", N, M);
    // Read in the content and initialize data: --------------------
	FruitList L = BuildFruitList();
    InitialChoose(L);

    // Input prices: -----------------------------------------------
    for (i = 0; i < M; i++) {
        id = read();
        price = read();
        prices[id] = price;
    }
	// Start the time: ---------------------------------------------
	srand(time(0));
    int start_time = clock();
    
    // Excuting the backtracking for 'Round' times: ----------------
    for(i = 0;i < Round;i ++) Backtracking(1, 1, L);
	
	// Finish the time: --------------------------------------------
	int finish_time = clock();
    
	// Output the result and time: ---------------------------------
	Print();
	printf("\ntotal time: %f sec for %d rounds", (double)(finish_time - start_time) / CLOCKS_PER_SEC,Round);
	printf("\naverage time: %f sec", (double)(finish_time - start_time) / (CLOCKS_PER_SEC * Round));
    
	fclose(stdin);
//    system("pause");
    return 0;
}
