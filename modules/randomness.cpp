#include "randomness.h"

double normal_distribution_generator(void){

	/* Based on https://en.cppreference.com/w/cpp/numeric/random/normal_distribution */

	random_device rd{};
    mt19937 gen{rd()};

	normal_distribution<float> d{0,1};

	map<int, int> hist{};

	return round(d(gen));

}