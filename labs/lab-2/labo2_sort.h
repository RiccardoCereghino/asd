#include <vector> 
#include <stdlib.h>     // srand, rand, per quickSortRandom() da implementare
#include <time.h>

using namespace std;


void selectionSort(vector<int>&);
void insertionSort(vector<int>&);
void bubbleSort(vector<int>&);
void mergeSort(vector<int>&);
void quickSortTrivial(vector<int>&);
void quickSortRandom(vector<int>&);
void qs(vector<int>&,int,int);
int partition_in_place(vector<int>&, int, int);
int partition_in_place_random(vector<int>&, int, int);
void swap(int&, int&);
void qs_rand(vector<int>&,int,int);