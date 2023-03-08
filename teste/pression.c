#include <stdio.h>

int main(void) {
	// your code goes here
	int caliberTo = 0;
	int currentPression = 0;

do{

    scanf("%d", &caliberTo);
} while((caliberTo < 1) || (caliberTo > 40));

do{

	scanf("%d", &currentPression);
	} while((currentPression < 1) || (currentPression > 40));



	int more = caliberTo - currentPression;
	printf("%d\n", more);
	return 0;
}

