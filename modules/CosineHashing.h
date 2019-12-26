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

using namespace std;

extern ifstream inFile; /* Input File */

extern ifstream qFile; /* Query File */

extern ofstream outFile; /* Output File */

static std::vector<std::vector<std::vector<int>>> Hash_Tables; /* Hash Tables */

static vector<vector<double> > Hash_Function(10, vector<double> (10)); /* Hash Functions */

static vector<vector<int> > Amplified_Functions(10, vector<int> (10)); /* Amplified Hash Functions */

static vector<int> points_in_range;

static unsigned int dimension;

static long long unsigned int no_lines;

void HashTable_Cosine_Initialization(int L,int k); /* Hash Table Initializer */

void HashFunctions_Cosine_Initialization(int L,int k); /* Hash Functions Initializer */

void Cosine_Hash_from_file(int line,int L,int k); /* Hashes a specific line of a file */

void Hash_Tables_Finalization(int L, int k); /* Finilizes all Operation on Creating the Hash Tables*/

void print_Hash_Table_Vector(int amp_func,int pos); /* Prints a specific Vector on the Hash Table */

int hash_query(int line, int amp_func,int k); /* hashes a specific line of the query file */

void Search_Hash_Tables(int line,int L,int k); /* For Debugging purposes - Searches where a value is in the Hash Tables */

double calcute_cosine_distance(int input_line, int query_line); /* Returns Cosine dist between input line and query line */

void Cosine_Full_Search_NN(int query_line); /* Brute Force Nearest Neighbour Search using Cosine metric */

void Cosine_Full_Search_Range(int query_line,double radius);  /* Brute Force Range Search using Cosine metric */

void Nearest_Query_Cosine(int query_line,int L,int k); /* Returns Nearest Query using cosine similarity */

void print_Hash_Functions(int amp_func); /* For debugging purposes - Prins Hash Function Members */

void Range_Search_Cosine(int query_line,double range,int L,int k); /* Returns all vectors in range */

void Cosine_LSH_File(int L,int k); /* Calls the appropriate functions to perform LSH queries */