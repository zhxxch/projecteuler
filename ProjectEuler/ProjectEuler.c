#include<stdio.h>
#include"Header.h"
/* Problem #206 */

int main(int argc, char *argv[]){
    long long ans = find_sqrt();
    printf("sqrt = %lli, sq = %lli\n", ans, ans*ans);
	return 0;
}