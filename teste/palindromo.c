#include<stdio.h>
#include<stdlib.h>

// lista pra teste 90 10 20 40 60 20 20 30 40 50

int main(void) {
	// your code goes
	int items = 0;
	do{
		scanf("%d", &items);
	}while((items < 0) || (items > 106));


	char temp;
    scanf("%c", &temp);

	char t[1000];
	int listaNum[items];

	for(int j = 0; j < items; j++)
	{
		listaNum[j] = 0;
	}

    scanf("%[^\n]", t);

    int i = 0;
    int j = 0;
    while(t[i] != '\0')
    {
    	if (t[i] != 32)
    	{
    		listaNum[j] = listaNum[j] + atoi(&t[i]);

    	}
    	else
    	{
    		j++;
    	}
    	i++;
    }

    int resposta = 0;
    int loops = 0;



   	loops = items / 2;

    for (int z = 0; z < loops; z++)
    {

    	if (listaNum[z] != listaNum[ (items - 1) - z ])
    	{
            //printf("%d\n", listaNum[z]);
           // printf("%d\n", (listaNum[ (items - 1) - z ]));
            //printf("%d\n", (listaNum[ (items - 2) - z ]));
    		if ((listaNum[z] + listaNum[z + 1]) == listaNum[ (items - 1) - z ])
    	    {

    	        z++;
    	        items++;
    	        //loops--;
    	        resposta++;
    	    }
    		else if (listaNum[z] == (listaNum[ (items - 1) - z ] + listaNum[ (items - 2) - z ]))
    		{
    		    items--;
    	        loops--;
    		    resposta++;
    		}
    	}
    }
    printf("%d\n", resposta);
	return 0;
}

