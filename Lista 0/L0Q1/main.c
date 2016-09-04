/*L0Q1 - fcma*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a [100001], b [100001], soma [100001];

int main()
{
    freopen ("L0Q1.in", "r", stdin);
    freopen ("L0Q1.out", "w", stdout);

    int n, tamA, tamB, aux, cOut;

    //numero de entradas
    for (scanf ("%d", &n); n>0; n--){

        //coleta os numeros
        scanf ("%s", a);
        scanf ("%s", b);

        //coleta o numero de digitos dos numeros (com o \0)
        tamA = strlen (a);
        tamB = strlen (b);

        if (tamA>tamB) //maior
            aux = tamA;
        else
            aux = tamB;

        //fim da string
        soma[aux] = '\0';
        aux--;
        tamA--;
        tamB--;

        cOut = 0;

        //somar todos os digitos
        while (aux >= 0){

            //somar o tamanho igual da string
            while (tamA >= 0 && tamB >= 0){
                soma[aux] = a[tamA] + b[tamB] + cOut - '0';

                if (soma[aux] > '9'){
                    soma [aux] = soma [aux] - 10;
                    cOut = 1;
                }
                else{
                    cOut = 0;
                }

                tamB--;
                tamA--;
                aux--;
            }


            //strings de tamanhos diferentes
            for ( ;tamA>=0; tamA--, aux--){
                soma[aux] = a[tamA] + cOut;

                if (soma[aux] > '9'){
                    soma [aux] = soma [aux] - 10;
                    cOut = 1;
                }
                else{
                    cOut = 0;
                }
            }

            for ( ;tamB>=0; tamB--, aux--){
                soma[aux] = b[tamB] + cOut;

                if (soma[aux] > '9'){
                    soma [aux] = soma [aux] - 10;
                    cOut = 1;
                }
                else{
                    cOut = 0;
                }
            }


        }

        //imprimir saida
        if (n!= 1){
            if (cOut == 1)
                printf ("%d%s\n", cOut, soma);
            else
                printf ("%s\n", soma);
        }
        else{ //não imprimir o \n a mais
            if (cOut == 1)
                printf ("%d%s", cOut, soma);
            else
                printf ("%s", soma);
        }
    }

    return 0;
}
