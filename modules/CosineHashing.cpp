#include "CosineHashing.h"

using namespace std;

void HashTable_Cosine_Initialization(int L,int k){

	/* We have L hash tables with 2^k size each */

	Hash_Tables.resize(L,vector <vector <int> >(pow(2,k), vector <int> (1000)));

	// Hash_Function.resize( L ,vector<double>(pow(2,k)));

	cout << "I just resized the Hash tables with size: " << L << " x " << pow(2,k) << endl;

}

void HashFunctions_Cosine_Initialization(int L,int k){

	/* We have k hash functions with dim size each */

	dimension = get_dim_of_data();

	no_lines = get_number_of_lines();

	Hash_Function.clear();

	Hash_Function.resize(dimension ,vector<double>(k));

	cout << "I just resized the Hash Functions with size: " << k << " x " << dimension << endl;

	/* Initializing the ri vectors used for the cosine similarity */

	for(int i=0;i<k;i++){

		for(int j=0;j < dimension;j++){

			Hash_Function[i][dimension] = normal_distribution_generator();

			// cout << "i: " << i << " j: " << j << " is " << (double) Hash_Function[i][j] << endl; /* DEBUG - Printing out elements of Hash_Function */

		}

	}

	/* Initializing Amplified Hash Functions */

	Amplified_Functions.resize( k ,vector<int>(L));

	srand(time(0));

	int func_num;

	int j;

	for(int i=0; i<L; i++){

		j=0;

		Amplified_Functions[i].clear();

		do{

			func_num = rand() % k;

			// cout << "func_num is: " << func_num << "i is: " << i << endl;

			if( find(Amplified_Functions[i].begin(), Amplified_Functions[i].end(), func_num ) == Amplified_Functions[i].end()){

				// cout << "i got in here with value: " << func_num << " i is: " << i << endl;
				j++;

				Amplified_Functions[i].push_back(func_num);

			}

		}while(j < k);

	}

	/* DEBUG - Printing Amplified Hash Func Elements */

	// for(int i=0;i<k;i++){

	// 	for(int j=0;j<get_dim_of_data();j++){

	// 		cout << Hash_Function[i][j] << '\t';

	// 	}

	// 	cout << endl;
	// }

	/* -------------------------------------------- */

}

void Cosine_Hash_from_file(int line,int L,int k){

	/* First lets get to the line pointed */

	move_input_to_line(line);

	double x;

	/* Now onto hashing! */

	long long int sum;

	short int pos;

	int h;

	for(int amp_func = 0;amp_func < L; amp_func++ ){ /* We have to hash each vector with each Amplified function */

		pos = 0;

		for(h = 0 ; h < k ; h++ ){ /* We have to hash each vector with each Hash Function in the amp_func Amplified Function */

			sum = 0; /* Each time, we have to find the total sum of the inner product */

			for(int i = 0 ; i < dimension ; i++ ){ /* In order to calculate the Inner product of the hash vecor and the data vector we have to multiply all of their coordinates */

				// if( i == 0 ) inFile >> x; /* First int is an id, so skip it */

				inFile >> x; /* Get the first int from the file */

				// cout << "Adding to  " << sum << " with " << x* Hash_Function[ Amplified_Functions[amp_func][h] ][i] << endl;

				sum = sum + x * Hash_Function[ Amplified_Functions[amp_func][h] ][i]; /* Sum is calculating the inner product of the two vectors */

			}

			move_input_to_line(line); /* Reset the line for the next hash function */

			if( sum >= 0 ) pos = pos + pow(2,h); /* Cosine Hashing */

		}

		Hash_Tables[amp_func][pos].push_back(line);

	}

}

void Hash_Tables_Finalization(int L, int k){
	
	int max = pow(2,k);

	for( int amp_func=0; amp_func< L; amp_func++ ){

		for(int pos=0; pos< max; pos++){
	
			Hash_Tables[amp_func][pos].erase(remove(Hash_Tables[amp_func][pos].begin(), Hash_Tables[amp_func][pos].end(), 0), Hash_Tables[amp_func][pos].end());

		}
	}

	Cosine_Hash_from_file(0,L,k);

}

void print_Hash_Table_Vector(int amp_func,int pos){

	cout << "Printing Hash Table [" << amp_func << "][" << pos << "] with size: " << Hash_Tables[amp_func][pos].size() << endl;

	for (auto i = Hash_Tables[amp_func][pos].begin(); i != Hash_Tables[amp_func][pos].end(); ++i) cout << *i << ' ';

}

void print_Hash_Functions(int amp_func){

	cout << "Printing Hash Functions [" << amp_func << "]" << endl;

	for (auto i = Hash_Function[amp_func].begin(); i != Hash_Function[amp_func].end(); ++i) cout << *i << ' ';

}

void Search_Hash_Tables(int line,int L,int k){

	for(int i=0;i<L;i++){ 

		for(int j=0;j<pow(2,k);j++){

			for (auto k = Hash_Tables[i][j].begin(); k != Hash_Tables[i][j].end(); k++){

				if( *k == line ) cout << " FOUND " << line << "IN " << i << " hashtable and in pos " << j << endl;

			}
		}
	}
}


int hash_query(int line, int amp_func,int k){

	/* First lets move to the line of thr query file we have to hash */

	get_query(line);

	/* Now lets hash the query line with the amp_func given */

	long long int sum;

	short int pos=0;

	int h;

	double x;

	for(h = 0 ; h < k ; h++ ){ 			/* We have to hash each vector with each Hash Function in the amp_func Amplified Function */

		sum = 0; 						/* Each time, we have to find the total sum of the inner product */

		for(int i = 0 ; i < dimension ; i++ ){ /* In order to calculate the Inner product of the hash vecor and the data vector we have to multiply all of their coordinates */

			// if( i == 0 ) inFile >> x; 	/* First int is an id, so skip it */

				qFile >> x; 			/* Get the first int from the file */

				sum = sum + x * Hash_Function[ Amplified_Functions[amp_func][h] ][i]; /* Sum is calculating the inner product of the two vectors */

			}

			get_query(line); 			/* Reset the line for the next hash function */

			if( sum >= 0 ) pos = pos + pow(2,h); /* Cosine Hashing */

		}

		return pos; /* Found position in the amp_func hash table, now return its pos */
	
}

double calcute_cosine_distance(int input_line, int query_line){

	/* First lets get the vectors specified in both the input and the query file */

	int dim = get_dim_of_data();

	get_query(query_line);

	move_input_to_line(input_line);

	// cout << "Calculating Distance Between input_line " << input_line << " and query_line " << query_line << endl;
 
	/* Now lets calcute the inner product of the two vectors and the norm of each one*/

	double x,y;

	int product=0,x_norm=0,y_norm=0;

	for(int i=0;i<dimension;i++){

		inFile >> x;

		qFile >> y;

		// cout << "x: " << x << " y: " << y << " x*x = " << x*x << " y*y= " << y*y << " product " << product+ x*y << endl;

		product = product + x*y;

		x_norm = x_norm + x*x;

		y_norm = y_norm + y*y;

	}

	x_norm = sqrt(x_norm);

	y_norm = sqrt(y_norm);

	// cout << "product: " << product << endl;
	// cout << " x_norm*y_norm: " << x_norm*y_norm << endl;

	double cosine_dist = product / static_cast<double>(x_norm*y_norm);

	// cout << "DIST: " << 1.0 - cosine_dist << endl;

	return cosine_dist;
}

void Cosine_Full_Search_NN(int query_line){

	get_query(query_line);

	long long unsigned int min_line=0;

	double min_dist=3.0,dist;

	for(long long unsigned int i=0;i< no_lines;i++){

		dist = calcute_cosine_distance(i,query_line);

		if(dist < min_dist){

			min_line = i;

			min_dist = dist;

		}

	}

	outFile << "Nearest Neighbour: Item " << min_line << endl;

	outFile << "distanceTrue: " << min_dist << endl;


}

void Cosine_Full_Search_Range(int query_line,double radius){

	get_query(query_line);

	outFile << "R-Near NeighboursTrue:" << endl;

	double dist;

	for(long long unsigned int i=1;i< no_lines;i++){

		dist = calcute_cosine_distance(i,query_line);

		if(dist < radius){

			outFile << "Item " << i << endl;

		}

	}

}

void Nearest_Query_Cosine(int query_line,int L,int k){

	int amp_func,pos_in_hash_table;

	double dist , min_dist=3.0;

	short int time_to_break = 3*L;

	long long unsigned int min_line;

	auto start1 = std::chrono::high_resolution_clock::now();

	for( amp_func = 0;amp_func < L; amp_func++ ){ /* We have to look in each hash table for the query vector */

		pos_in_hash_table = hash_query(query_line,amp_func,k);

		// cout << "pos in hash table: " << pos_in_hash_table << endl;

		for (auto i = Hash_Tables[amp_func][pos_in_hash_table].begin(); i != Hash_Tables[amp_func][pos_in_hash_table].end(); ++i){

			dist = calcute_cosine_distance(*i, query_line); /* Calculate cosine distance between the two vectors */ 

			if( dist < min_dist ){ /* If the distance we found is less, update min_dist and min_line */

				min_line = *i;

				min_dist = dist;

				// cout << "Updated min dist: " << min_dist << " min_line: " << min_line << endl;
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

	Cosine_Full_Search_NN(query_line);

	auto finish2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed2 = finish2 - start2;

	outFile << "tLSH: " << elapsed1.count() << endl;

	outFile << "tTrue: " << elapsed2.count() << endl;

	outFile << "==================================================== " << endl;		


}

void Range_Search_Cosine(int query_line,double range,int L,int k){

	short int already_in;

	int amp_func,pos_in_hash_table;

	double dist;

	auto start1 = std::chrono::high_resolution_clock::now();

	for( amp_func = 0;amp_func < L; amp_func++ ){ /* We have to look in each hash table for the query vector */

		pos_in_hash_table = hash_query(query_line,amp_func,k);

		// cout << "pos in hash table: " << pos_in_hash_table << endl;

		for (auto i = Hash_Tables[amp_func][pos_in_hash_table].begin(); i != Hash_Tables[amp_func][pos_in_hash_table].end(); ++i){

			dist = calcute_cosine_distance(*i, query_line); /* Calculate cosine distance between the two vectors */ 

			if( dist < range ){

				// cout << "possible point found: " << *i << endl;

				already_in = 0;

				for(auto j = points_in_range.begin(); j != points_in_range.end(); ++j){

					if( *j == *i ) already_in = 1;

				}

				if( already_in == 0 ) points_in_range.push_back(*i);

			} 


		}

	}

	auto finish1 = std::chrono::high_resolution_clock::now();

	outFile << "Query " << query_line << endl;
	outFile << "R-Near Neighbours: " << endl;

	for(auto j = points_in_range.begin(); j != points_in_range.end(); ++j){

		// cout << "Point " << *j << " is in range " << range << endl;
		outFile << "Item " << *j << endl;

	}

	std::chrono::duration<double> elapsed1 = finish1 - start1;

	auto start2 = std::chrono::high_resolution_clock::now();

	Cosine_Full_Search_Range(query_line,range);

	auto finish2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed2 = finish2 - start2;

	outFile << "tLSH: " << elapsed1.count() << endl;

	outFile << "tTrue: " << elapsed2.count() << endl;

	outFile << "==================================================== " << endl;



	points_in_range.clear();

}

void Cosine_LSH_File(int L,int k){

	string str;

	qFile >> str;

	// cout << str << endl;

	double radius;

	long long unsigned int queries;

	if(str.compare("Radius:") == 0 ){

		qFile >> radius;

		cout <<"Radius is " << radius << endl;

		queries = get_number_of_queries();

		for(int q=1;q<queries;q++){

			Range_Search_Cosine(q,radius,L,k);

		}
	} 
	else{

		queries = get_number_of_queries();

		for(int q=0;q<queries;q++){

			Nearest_Query_Cosine(q,L,k);


		}

	}

}