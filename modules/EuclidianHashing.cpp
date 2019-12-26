#include "EuclidianHashing.h"
#define BIG_INT 4294967291

using namespace std;

void HashTable_Euclidian_Initialization(int L){

	/* We have L hash tables with n/2 size each */

	n = get_number_of_lines();

	dim = get_dim_of_data();
	
	Euclidian_Hash_Tables.resize(L,vector <vector <long long unsigned int> >(n/2, vector <long long unsigned int> (1000)));

	cout << "I just resized the Hash tables with size: " << L << " x " << n/2 << endl;

}

void HashFunctions_Euclidian_Initialization(int k , int L){

	/* First lets fill out the v vectors used for the euclidian hashing method */

	v.resize( k ,vector<double>(dim));

	cout << "I just resized the Hash Functions with size: " << k << " x " << dim << endl;

	for(int i=0;i<k;i++){

		v[i].clear();

		for(int j=0;j < dim;j++){

			v[i].push_back(normal_distribution_generator() );

			// cout << "i: " << i << " j: " << j << " is " << (double) v[i][j] << endl; /* DEBUG - Printing out elements of Hash_Function */

		}

	}

	/* Now lets initialize the w which will be used */

	w = 400;

	/* Initialize Amplified_Euclidian_Functions */

	Euclidian_Amplified_Functions.resize( L , vector<int>(k));

	srand(time(0));

	int func_num;

	int j;

	for(int i=0; i<L; i++){

		j=0;

		Euclidian_Amplified_Functions[i].clear();

		do{

			func_num = rand() % k;

			// cout << "func_num is: " << func_num << "i is: " << i << endl;

			if( find(Euclidian_Amplified_Functions[i].begin(), Euclidian_Amplified_Functions[i].end(), func_num ) == Euclidian_Amplified_Functions[i].end()){

				// cout << "i got in here with value: " << func_num << " i is: " << i << endl;
				j++;

				Euclidian_Amplified_Functions[i].push_back(func_num);

			}

		}while(j < k);

	}

	/* Last but not least, lets initialize the t of each hash function */

	t.clear();

	float random;

	random_device generator;
	uniform_real_distribution<float> distribution (0.0, (float) w);

	for(int i=0;i<k;i++){ 	/* Each hash function has its own t */

		random = distribution(generator); /* Generate a new double number */

		t.push_back(random);

	}

}

void Search_Euclidian_Hash_Tables(int line,int L){

	for(int i=0;i<L;i++){ 

		for(int j=0;j<n/2;j++){

			for (auto k = Euclidian_Hash_Tables[i][j].begin(); k != Euclidian_Hash_Tables[i][j].end(); k++){

				if( *k == line ) cout << " FOUND " << line << "IN " << i << " hashtable and in pos " << j << endl;

			}
		}
	}
}

void Euclidian_Hash_from_file(int line, int L , int k ){

	/* First lets get to the line pointed */

	move_input_to_line(line);

	/* Now onto hashing! */

	string string_to_hash;

	long long int sum;

	double x;

	string str;

	long long unsigned int pos;

	for(int amp_func = 0;amp_func < L; amp_func++ ){ /* We have to hash each vector with each Amplified function */

		string_to_hash = "";

		for(int h = 0 ; h < k ; h++ ){ /* We have to hash each vector with each Hash Function in the amp_func Amplified Function */

			sum = 0;

			for(int i = 0 ; i < dim ; i++ ){ /* In order to calculate the Inner product of the hash vecor and the data vector we have to multiply all of their coordinates */

				// if( i == 0 ) inFile >> str; /* First int is an id, so skip it */

				inFile >> x; /* Get the first int from the file */

				// cout << "Adding to  " << sum << " with " << x* Hash_Function[ Amplified_Functions[amp_func][h] ][i] << endl;

				sum = sum + x * v[ Euclidian_Amplified_Functions[amp_func][h] ][i]; /* Sum is calculating the inner product of the two vectors */

			}

			sum = sum + t[h];

			sum = floor( sum / (double) w );

			move_input_to_line(line); /* Reset the line for the next hash function */

			string_to_hash.append(to_string(sum));

		}

		pos = modulo(hash<string>{}(string_to_hash), BIG_INT);

		pos = modulo(pos,n/2);

		// cout << "Pushing " << line << " to [" << amp_func << "][" << pos << "]" << endl; 

		Euclidian_Hash_Tables[amp_func][pos].push_back(line);

	}

}

void Euclidian_Hash_Tables_Finalization(int L){
	
	int max = n/2;

	for( int amp_func=0; amp_func< L; amp_func++ ){

		for(int pos=0; pos< max; pos++){
	
			Euclidian_Hash_Tables[amp_func][pos].erase(remove(Euclidian_Hash_Tables[amp_func][pos].begin(), Euclidian_Hash_Tables[amp_func][pos].end(), 0), Euclidian_Hash_Tables[amp_func][pos].end());

		}
	}

	Euclidian_Hash_from_file(0,L,k);

}


long long int calcute_euclidian_distance(int input_line, int query_line){

	/* First lets get the vectors specified in both the input and the query file */

	get_query(query_line);

	move_input_to_line(input_line);

	// cout << "Calculating Distance Between input_line " << input_line << " and query_line " << query_line << endl;
 
	/* Now lets calcute the inner product of the two vectors and the norm of each one*/

	double x,y;

	long long int dist=0;

	for(int i=0;i<dim;i++){

		inFile >> x;

		qFile >> y;

		dist = dist + (x-y)*(x-y);

		// cout << "x: " << x << " y: " << y << "dist: " << dist << endl;

	}

	// cout << "DIST: " << dist << endl;

	return dist;
}

long long unsigned int euclidian_hash_query(int query_line,int amp_func,int k){
	
	get_query(query_line);

	string string_to_hash;

	long long int sum;

	double x;

	long long unsigned int pos;

		string_to_hash = "";

		for(int h = 0 ; h < k ; h++ ){ /* We have to hash each vector with each Hash Function in the amp_func Amplified Function */

			sum = 0;

			for(int i = 0 ; i < dim ; i++ ){ /* In order to calculate the Inner product of the hash vecor and the data vector we have to multiply all of their coordinates */

				// if( i == 0 ) inFile >> x; /* First int is an id, so skip it */

				qFile >> x; /* Get the first int from the file */

				// cout << "Adding to  " << sum << " with " << x* Hash_Function[ Amplified_Functions[amp_func][h] ][i] << endl;

				sum = sum + x * v[ Euclidian_Amplified_Functions[amp_func][h] ][i]; /* Sum is calculating the inner product of the two vectors */

			}

			sum = sum + t[h];

			sum = floor( sum / (double) w );

			get_query(query_line); /* Reset the line for the next hash function */

			string_to_hash =  string_to_hash + to_string(sum);

		}

		pos = modulo(hash<string>{}(string_to_hash), BIG_INT);

		pos = modulo(pos,n/2);

		// cout << "Pushing " << line << " to [" << amp_func << "][" << pos << "]" << endl; 

		return pos;


}

void Euclidian_Full_Search_NN(int query_line){

	/* Brute Force Nearest Neighbour Search using Euclidian metric */

	get_query(query_line);

	long long unsigned int min_line=0,min_dist=BIG_INT ,dist;

	for(long long unsigned int i=0;i< n;i++){

		dist = calcute_euclidian_distance(i,query_line);

		if(dist < min_dist){

			min_line = i;

			min_dist = dist;

		}

	}

	outFile << "Nearest Neighbour: Item " << min_line << endl;

	outFile << "distanceTrue: " << min_dist << endl;

}

void Euclidian_Full_Search_Range(int query_line,double radius){

	/* Brute Force Range Search using Euclidian metric */

	get_query(query_line);

	outFile << "R-Near Neighbours:" << endl;

	long long unsigned int dist;

	for(long long unsigned int i=0;i< n;i++){

		dist = calcute_euclidian_distance(i,query_line);

		if(dist < radius){

			outFile << "Item " << i << endl;

		}

	}

}

void Nearest_Query_Euclidian(int query_line,int L,int k){

	/* Given a query line, finds its nearest Neighbour */

	int amp_func,pos_in_hash_table;

	long long unsigned int dist, min_dist = 2147483646;

	short int time_to_break = 3*L;

	long long unsigned int min_line=0;

	auto start1 = std::chrono::high_resolution_clock::now();

	for( amp_func = 0;amp_func < L; amp_func++ ){ /* We have to look in each hash table for the query vector */

		pos_in_hash_table = euclidian_hash_query(query_line,amp_func,k);

		// cout << "pos in hash table: " << pos_in_hash_table << endl;

		for (auto i = Euclidian_Hash_Tables[amp_func][pos_in_hash_table].begin(); i != Euclidian_Hash_Tables[amp_func][pos_in_hash_table].end(); ++i){

			dist = calcute_euclidian_distance(*i, query_line); /* Calculate cosine distance between the two vectors */ 

			if( dist < min_dist ){ /* If the distance we found is less, update min_dist and min_line */

				min_line = *i;

				min_dist = dist;
			}

			time_to_break--;

			if( time_to_break <= 0 ) break; 

		}

		time_to_break = 3*L;

	}

	auto finish1 = std::chrono::high_resolution_clock::now();

	// cout << "Nearest Vector of " << query_line << " is: " << min_line << " with distance: " << min_dist << endl;

	outFile << "Query " << query_line << endl;
	outFile << "NN(lsh): Item " << min_line << endl;
	outFile << "distanceLSH: " << min_dist << endl;

	auto start2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed1 = finish1 - start1;

	Euclidian_Full_Search_NN(query_line);

	auto finish2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed2 = finish2 - start2;

	outFile << "tLSH: " << elapsed1.count() << endl;

	outFile << "tTrue: " << elapsed2.count() << endl;

	outFile << "==================================================== " << endl;

}

void Range_Search_Euclidian(int query_line,double range,int L,int k){

	/* Given a query line, performs LSH range search */

	short int already_in;

	int amp_func,pos_in_hash_table;

	long long unsigned int dist;

	auto start1 = std::chrono::high_resolution_clock::now();

	for( amp_func = 0;amp_func < L; amp_func++ ){ /* We have to look in each hash table for the query vector */

		pos_in_hash_table = euclidian_hash_query(query_line,amp_func,k);

		// cout << "pos in hash table: " << pos_in_hash_table << " amp_func: " << amp_func << " k: " << k << " query_line: " << query_line << " range: " << range << endl;

		for (auto i = Euclidian_Hash_Tables[amp_func][pos_in_hash_table].begin(); i != Euclidian_Hash_Tables[amp_func][pos_in_hash_table].end(); ++i){

			dist = calcute_euclidian_distance(*i, query_line); /* Calculate cosine distance between the two vectors */

			// cout << "Found distance between " << *i << " and " << query_line << " : " << dist << endl;

			if( (double) dist < range ){

				// cout << "possible point found: " << *i << endl;

				already_in = 0;

				for(auto j = points_in_range_euc.begin(); j != points_in_range_euc.end(); ++j){

					if( *j == *i ) already_in = 1;

				}

				if( already_in == 0 ) points_in_range_euc.push_back(*i);

			} 


		}

	}

	auto finish1 = std::chrono::high_resolution_clock::now();

	outFile << "Query " << query_line << endl;
	outFile << "R-Near Neighbours: " << endl;

	for(auto j = points_in_range_euc.begin(); j != points_in_range_euc.end(); ++j){

		// cout << "Point " << *j << " is in range " << range << endl;
		outFile << "Item " << *j << endl;
	}

	std::chrono::duration<double> elapsed1 = finish1 - start1;

	// auto start2 = std::chrono::high_resolution_clock::now();

	// Euclidian_Full_Search_Range(query_line,range);

	// auto finish2 = std::chrono::high_resolution_clock::now();

	// std::chrono::duration<double> elapsed2 = finish2 - start2;

	outFile << "tLSH: " << elapsed1.count() << endl;

	// outFile << "tTrue: " << elapsed2.count() << endl;

	outFile << "==================================================== " << endl;
	points_in_range_euc.clear();

}

void Euclidian_LSH_File(int L,int k){

	/* Calls the appropriate functions to perform LSH queries */

	string str;

	qFile >> str;

	cout << str << endl;

	double radius;

	long long unsigned int queries;

	if(str.compare("Radius:") == 0 ){

		qFile >> radius;

		cout << "radius is " << radius << endl;

		queries = get_number_of_queries();

		for(int q=1;q<queries;q++){

			Range_Search_Euclidian(q,radius,L,k);

		}
	} 
	else{

		queries = get_number_of_queries();

		for(int q=0;q<queries;q++){

			Nearest_Query_Euclidian(q,L,k);

		}

	}

}

