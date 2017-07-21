#include<stdio.h>
#include"Header.h"
/* Problem #586 */

int main(int argc, char *argv[]){
	const long long input = 10000ll;
	const long long ways = 4ll;
	printf("f(%lli, %lli) = %lli\n", input, ways, f(input, ways));
	system("pause");
	return 0;
}