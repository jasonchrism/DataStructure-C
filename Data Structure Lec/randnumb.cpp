#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	srand(time(0));
	int num = rand() % 100 + 1;
	printf("%d", num);
}
