#include <stdio.h>

int main(void) {
	// your code goes here

	int fernanda = 0;


	int idades[3];

for(int i = 0; i < 3; i++)
{
	do{
		scanf("%d", &idades[i]);
	} while((idades[i] < 5) || (idades[i] > 100));
}

for(int j = 0; j < 3; j++)
{
	for(int i = 0; i < 3; i++)
	{
		if(idades[j] > idades[i])
		{
			int temp = idades[j];
			idades[j] = idades[i];
			idades[i] = temp;
 		}
	}
}


	fernanda = idades[1];
	printf("%d\n", fernanda);
	return 0;
}

