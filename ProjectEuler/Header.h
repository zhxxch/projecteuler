#pragma once
/* Problem #586 */
#include<math.h>
#include<stdlib.h>
#include<essixtence/check.h>
#include<essixtence/zxcrypto.h>

inline int test_ab(const long long remainder, const long long a, const long long b) {
	return remainder == a*b;
}

long test_ab_num(const long long remainder, const long long sumab) {
	long long count = 0;
	for (long long a = 1; a < remainder; a++) {
		for (long long b = 1; b <= (remainder - a); b++) {
			if (test_ab(remainder, a, b)) {
				count++;
			}
		}
	}
	return count;
}

long find_ways_count(const long long input_number, long long ab_remainder[], const long long sq_table[]) {
	long long count = 0;
	const long long max_sqrt = (long long)sqrt(input_number) + 1;
	for (long long input_sqrt = 0; input_sqrt < max_sqrt; input_sqrt++) {
		ab_remainder[input_sqrt] = input_number - sq_table[input_sqrt];
	}
	for (long long input_sqrt = 0; input_sqrt < max_sqrt; input_sqrt++) {
		count += test_ab_num(ab_remainder[input_sqrt], input_sqrt);
		if (count > 40)break;
	}
	return count;
}

void perfect_sq(long long arr[], const long long max_sqrt) {
	for (long long i = 0; i < max_sqrt; i++) {
		arr[i] = i*i;
	}
}

long log_table(double arr[], const long long max_input) {
	return 0;
}

long long f(const long long max_input, const long long ways) {
	long long count = 0;
	const long long max_sqrt = (long long)sqrt(max_input) + 1;
	long long *ab_remainder = malloc(max_sqrt * sizeof max_input);
	long long *sq_table = malloc(max_sqrt * sizeof max_input);
	perfect_sq(sq_table, max_sqrt);
	for (long long curr_test_num = 0; curr_test_num <= max_input; curr_test_num++) {
		if (find_ways_count(curr_test_num, ab_remainder, sq_table) == 40) {
			count++;
		}
	}
	free(ab_remainder);
	free(sq_table);
	return count;
}