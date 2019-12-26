#include "modulo_func.h"

long long int modulo(long long int a, long long int b){

    /* Modulo between a and b, supports negative numers */

	return (a % b + b) %b;

}