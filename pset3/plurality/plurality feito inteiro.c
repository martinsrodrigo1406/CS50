#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define MAX 9

typedef struct{
    int votos;
    string nome;
}candidate;

bool vote(string);
void print_winner(void);
int numCand = 0;

candidate listaCand[MAX];

int main(int argc, char *argv[])
{
    int eleitoresNum = 0;
    numCand = argc - 1;


    printf("argc = %d\n", argc);

//inicializando e populando candidatos e zerando votos
    for(int i = 0; i < (numCand); i++)
    {
        listaCand[i].nome = argv[i + 1];
        listaCand[i].votos = 0;
    }

//obtendo entrada do usuário sobre numero de eleitores
    do{
        eleitoresNum = get_int("Número de eleitores: ");
    } while(eleitoresNum <= 0 || isdigit(eleitoresNum) != 0);


//chamando funcao voto
    for(int i = 0; i < eleitoresNum; i++)
    {
        bool valid = false;

        do{
            string candVotado = get_string("Voto: ");
            valid = vote(candVotado);

        }while(valid == false);
    }



//ordenando mais votados

candidate vencedor;

    for(int i = 0; i < (numCand - 1); i++)
    {
        for(int j = 0; j < (numCand - i) - 1; j++)
        {
            if(listaCand[j].votos > listaCand[j + 1].votos)
            {
                vencedor = listaCand[j];
                listaCand[j] = listaCand[j + 1];
                listaCand[j + 1] = vencedor;
            }
        }
    }

//imprimindo o vencedor
    print_winner();
    return 0;
}

bool vote(string name)
{
    bool resposta = false;
    for(int n = 0; n < numCand; n++)
            {
                if(strcmp(name, listaCand[n].nome) == 0)
                {
                    listaCand[n].votos++;
                    resposta = true;
                }
            }
            if(resposta == false)
            {
                printf("Voto inválido.\n");
            }
            return resposta;
}

void print_winner(void)
{
    for(int z = (numCand - 2); z >= 0; z--)
    {
        if(listaCand[z].votos >= listaCand[numCand - 1].votos)
        {
             printf("%s\n", listaCand[z].nome);
        }
    }
    printf("%s\n", listaCand[numCand - 1].nome);
}