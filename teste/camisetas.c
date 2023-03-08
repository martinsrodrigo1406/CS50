#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// your code goes here

	int premiados = 0;
	int camisetasPequenas = 0;
	int camisetasMedias = 0;
	int ganhadoresPequenas = 0;
	int ganhadoresMedias = 0;

	do{
		scanf("%d", &premiados);
	} while((premiados < 1) || (premiados > 1000));


    // temp statement to clear buffer
    char temp;
    scanf("%c", &temp);

	char t[2000];

    scanf("%[^\n]", t);
    int i = 0;
    while(t[i] != '\0')
    {
    	if(t[i] == '1')
    	{
    		ganhadoresPequenas++;
    	}
    	else if(t[i] == '2')
    	{
    		ganhadoresMedias++;
    	}

    	i++;
    }

	do{
		scanf("%d", &camisetasPequenas);
	} while((camisetasPequenas < 0) || (camisetasPequenas > 1000));

	do{
		scanf("%d", &camisetasMedias);
	} while((camisetasMedias < 0) || (camisetasMedias > 1000));

	if(ganhadoresPequenas < camisetasPequenas)
	{
		printf("N\n");
		return 0;
	}

	if(ganhadoresMedias < camisetasMedias)
	{
		printf("N\n");
		return 0;
	}


    printf("S\n");
	return 0;
}


