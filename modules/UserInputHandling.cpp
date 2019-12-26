#include "UserInputHandling.h"

using namespace std;

int user_input_handling(int argc, char *argv[]){ 

	int file_to_output = 0;

	short int cur_arg = 1;

	short int input_given = 0;

	short int query_given = 0;

	short int output_given = 0;

	short int metric_given = 0;
	
	while( cur_arg < argc ){

		if( strcmp(argv[cur_arg],"-d") == 0 ){	/* Checking for Input File */

			if( cur_arg == (argc - 1) || strcmp(argv[cur_arg+1],"-d") == 0 || strcmp(argv[cur_arg+1],"-q") == 0 || strcmp(argv[cur_arg+1],"-k") == 0 || strcmp(argv[cur_arg+1],"-L") == 0 || strcmp(argv[cur_arg+1],"-o") == 0 || strcmp(argv[cur_arg+1],"-M") == 0 || strcmp(argv[cur_arg+1],"-probes") == 0 ){

				cout << "Please specify an Input file." << endl;

				return -1;
			}
			else{

				inFile.open(argv[cur_arg+1]);

				input_given = 1;

				if(!inFile){

					cout << "Could not find specified Input file.The program will now exit." << endl;

					return -1;

				}

			}

		}else if( strcmp(argv[cur_arg],"-q") == 0 ){ /* Checking for Query File */

			if( cur_arg == (argc - 1) || strcmp(argv[cur_arg+1],"-d") == 0 || strcmp(argv[cur_arg+1],"-q") == 0 || strcmp(argv[cur_arg+1],"-k") == 0 || strcmp(argv[cur_arg+1],"-L") == 0 || strcmp(argv[cur_arg+1],"-o") == 0 || strcmp(argv[cur_arg+1],"-M") == 0 || strcmp(argv[cur_arg+1],"-probes") == 0  ){

				cout << "Please specify a Query file." << endl;

				return -1;
			}
			else{

				qFile.open(argv[cur_arg+1]);

				query_given = 1;

				if(!qFile){

					cout << "Could not find specified Query file.The program will now exit." << endl;

					return -1;

				}

			}

		}else if( strcmp(argv[cur_arg],"-k") == 0 ){ /* Checking for k */

			if( cur_arg == (argc - 1) || strcmp(argv[cur_arg+1],"-d") == 0 || strcmp(argv[cur_arg+1],"-q") == 0 || strcmp(argv[cur_arg+1],"-k") == 0 || strcmp(argv[cur_arg+1],"-L") == 0 || strcmp(argv[cur_arg+1],"-o") == 0 || strcmp(argv[cur_arg+1],"-M") == 0 || strcmp(argv[cur_arg+1],"-probes") == 0 ){

				cout << "Please specify a value for k." << endl;

				return -1;
			}
			else k = atoi(argv[cur_arg+1]);

		}else if( strcmp(argv[cur_arg],"-L") == 0  ){ /* Checking for L */

			if( cur_arg == (argc - 1) || strcmp(argv[cur_arg+1],"-d") == 0 || strcmp(argv[cur_arg+1],"-q") == 0 || strcmp(argv[cur_arg+1],"-k") == 0 || strcmp(argv[cur_arg+1],"-L") == 0 || strcmp(argv[cur_arg+1],"-o") == 0 || strcmp(argv[cur_arg+1],"-M") == 0 || strcmp(argv[cur_arg+1],"-probes") == 0  ){

				cout << "Please specify a value for L." << endl;

				return -1;
			}
			else L = atoi(argv[cur_arg+1]);

		}else if( strcmp(argv[cur_arg],"-o") == 0 ){ /* Checking for Query File */

			if( cur_arg == (argc - 1) || strcmp(argv[cur_arg+1],"-d") == 0 || strcmp(argv[cur_arg+1],"-q") == 0 || strcmp(argv[cur_arg+1],"-k") == 0 || strcmp(argv[cur_arg+1],"-L") == 0 || strcmp(argv[cur_arg+1],"-o") == 0 || strcmp(argv[cur_arg+1],"-M") == 0 || strcmp(argv[cur_arg+1],"-probes") == 0  ){

				cout << "Please specify an output file." << endl;

				return -1;
			}else{

				outFile.open(argv[cur_arg+1]);

				output_given = 1;

				if(!outFile){

					cout << "Could not find/create specified output file.The program will now exit." << endl;

					return -1;

				}

			}

		}else if( strcmp(argv[cur_arg],"-metric") == 0 ){ /* Find metric */

			if( cur_arg == (argc - 1) || strcmp(argv[cur_arg+1],"-d") == 0 || strcmp(argv[cur_arg+1],"-q") == 0 || strcmp(argv[cur_arg+1],"-k") == 0 || strcmp(argv[cur_arg+1],"-L") == 0 || strcmp(argv[cur_arg+1],"-o") == 0 || strcmp(argv[cur_arg+1],"-M") == 0 || strcmp(argv[cur_arg+1],"-probes") == 0  ){

				cout << "Please specify a metric to be used." << endl;

				return -1;

			}else{

				if( strcmp(argv[cur_arg+1],"cosine") == 0 ){

					metric = 1;

				}

			}

		}else{

			cout << "Invalid Arguments Given.Available Arguments are:" << endl;

			cout << "-d -k -o -L -metric" << endl;

			return -1;

		}

		cur_arg = cur_arg + 2;
	}

	string str;

	if( input_given == 0 ){ /* If the user has not specified an input file, ask for it */

		cout << "Please specify an input file: ";

		cin >> str;

		inFile.open(str);

		if(!inFile){

			cout << "Could not find specified Input file." << endl;

			return -1;

		}

	}

	if( query_given == 0 ){ /* If the user has not specified a query file, ask for it */

		cout << "Please specify a query file: ";

		cin >> str;

		qFile.open(str);

		if(!qFile){

			cout << "Could not find specified Query file." << endl;

			return -1;

		}

	}

	if( output_given == 0 ){ /* If the user has not specified an output file via the CL, ask for it */

		cout << "Please specify an output file: ";

		cin >> str;

		outFile.open(str);

		if(!outFile){

			cout << "Could not find specified Output file." << endl;

			return -1;

		}

	}

	return 0;
}

long long unsigned int get_number_of_lines(void){

	/* First find out how many lines the dataset has */

	long long unsigned int lines=0; 	/* Im using a long long unsigned int for maximum range */

	string str;

	while( getline(inFile,str) ) ++lines;

	// cout << "Input line: " << lines << endl;

	inFile.clear();
	inFile.seekg(0,ios::beg);

	return lines;
}

long unsigned int get_dim_of_data(void){

	long unsigned int dim = 0;

	string str;

	getline(inFile,str);

	for(int i = 0; i < str.size(); i++ ){

		if(str[i]== ' ') dim++;

	}


	// dim--;


	inFile.clear();
	inFile.seekg(0,ios::beg);

	return dim;
}

void move_input_to_line(int line){

	string str;

	inFile.clear();
	inFile.seekg(0,ios::beg);

	for(int i=1;i<=line;i++) getline(inFile,str);

	// cout << "line " << line << " : " << str << endl;

}

void get_query(int query_line){

	string str;

	qFile.clear();
	qFile.seekg(0,ios::beg);

	for(int i=0;i<query_line;i++) getline(qFile,str);

	// cout << str << endl;

}

long long unsigned int get_number_of_queries(void){

	/* Finds out how many lines the query file has */

	long long unsigned int lines=0; 	/* Im using a long long unsigned int for maximum range */

	string str;

	while( getline(qFile,str) ) ++lines;

	cout << "Queries: " << lines << endl;

	qFile.clear();
	qFile.seekg(0,ios::beg);

	return lines;
}
