#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;

extern ifstream inFile; /* Input File */

extern ifstream qFile; /* Query File */

extern ofstream outFile; /* Output File */

extern int k; /* Number of LSH Functions */

extern int L; /* Number of Hash Tables */

extern bool metric; /* Metric to be used 0: Euclidian 1: Cosine */

int user_input_handling(int argc, char *argv[]); /* Handling of Command Line Arguments & File Opening */

long long unsigned int get_number_of_lines(void); /* Returns the number of lines in the dataset */

long unsigned int get_dim_of_data(void); /* Returns the dim of the data given */

void move_input_to_line(int line); /* Moves the inFile pointer to a specific line */

void get_query(int query_line); /* Returns a specific query from the query File */

long long unsigned int get_number_of_queries(void); /* Finds out how many lines the query file has */