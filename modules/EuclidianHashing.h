#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>
#include "UserInputHandling.h"
#include "randomness.h"
#include "modulo_func.h"

using namespace std;

extern ifstream inFile; /* Input File */

extern ifstream qFile; /* Query File */

extern ofstream outFile; /* Output File */

static vector<vector<vector<long long unsigned int>>> Euclidian_Hash_Tables; /* Hash Tables */

static vector<vector<double> > v; /* Vectors V used in Hash Functions */

static long long int n;

static int dim;

static vector< vector<int> > Euclidian_Amplified_Functions; /* Amplified Hash Functions */

static int w;

static vector<double> t;

static vector<int> points_in_range_euc;

void HashTable_Euclidian_Initialization(int L); /* Initializes the Euclidian Hash Tables */

void HashFunctions_Euclidian_Initialization(int k , int L); /* Initializes the Euclidian Hash Functions*/

void Euclidian_Hash_from_file(int line, int L , int k ); /* Euclidian LSH - Hash File */

void Search_Euclidian_Hash_Tables(int line,int L); /* For debugging purposes, searches for a value in the Hash Table */

void Euclidian_Hash_Tables_Finalization(int L); /* Finilization of Hash tables */

void Euclidian_LSH_File(int L,int k); /* Calls the appropriate functions to perform LSH queries */

long long int calcute_euclidian_distance(int input_line, int query_line); /* Calculates euclidian distance between a and b */

void Euclidian_Full_Search_NN(int query_line); /* Brute Force Nearest Neighbour Search using Euclidian metric */

void Nearest_Query_Euclidian(int query_line,int L,int k); /* Given a query line, finds its nearest Neighbour */

void Euclidian_Full_Search_Range(int query_line,double radius); /* Brute Force Range Search using Euclidian metric */

void Range_Search_Euclidian(int query_line,long long unsigned int range,int L,int k); /* Given a query line, performs LSH range search */