//L4Q1 de fcma
#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    int numero;
    struct Lista *prox;
}lista;

lista **vetor;

/*A função cria um novo nó para a lista com um parametro numero*/
lista* novoNo (int numero){
    lista *novo;

    novo = (lista*) malloc (sizeof (lista));

    if (novo != NULL){ //verificar erro
        novo->numero = numero;
        novo->prox = NULL;
    }
    return novo;
}

void imprimeLista (lista* aux){
    printf ("Lista:");
    while (aux != NULL){
        printf ("%d ", aux->numero);
        aux = aux->prox;
    }
    printf ("\n");
}

/*A função insere o numero em uma posicao no vetor, procurando sua localização de acordo com as regras da questão*/
void insere (int numero, int posicao){
    lista *aux, *aux2;
    int impar, achou=0;

    aux = vetor [posicao];

    if (aux == NULL){ //posicao livre
        vetor [posicao] = novoNo (numero);
    }
    else{ //posicao ocupada
        //imprimeLista(aux);
        aux2 = novoNo (numero); //cria o novo nó

        //procurar a posição adequada
        impar = (aux2->numero)%2; //se impar for == a 0, então é pq o número é par

        if (impar == 0){ //se for par

            if (aux->numero%2 == 1){ //se o primeiro elemento for impar
                aux2->prox = aux;
                vetor[posicao] = aux2;
            }
            else{
                while (aux->numero%2 == 0 && !achou){
                    if (aux->numero > aux2->numero){
                        if (aux->prox != NULL){
                            if (aux->prox->numero > aux2->numero && aux->prox->numero%2 == 0){
                                aux = aux->prox;
                            }
                            else{
                                achou = 1;
                                aux2->prox = aux->prox;
                                aux->prox = aux2;
                            }
                        }
                        else{
                            achou = 1;
                            aux->prox = aux2;
                        }
                    }
                    else{
                        achou = 1;
                        aux2->prox = aux;
                        vetor[posicao] = aux2;
                    }
                }
            }
        }

        else{ //número ímpar
            while (aux->prox != NULL){
                if (aux->prox->numero%2 ==0){
                    aux = aux->prox;
                }
                else{
                    break;
                }
            }
            if (aux->prox == NULL){
                aux->prox = aux2;
            }
            else if (aux->prox->numero > aux2->numero){
                aux2->prox = aux->prox;
                aux->prox = aux2;
            }
            else{
                aux = aux->prox;
                while (aux->numero%2 == 1 && !achou){
                    if (aux->numero < aux2->numero){
                        if (aux->prox != NULL){
                            if (aux->prox->numero < aux2->numero){
                                aux = aux->prox;
                            }
                            else{
                                achou = 1;
                                aux2->prox = aux->prox;
                                aux->prox = aux2;
                            }
                        }
                        else{
                            achou = 1;
                            aux->prox = aux2;
                        }
                    }
                }
            }
        }
    }

}

void liberaLista (lista* aux){
    lista* i;

    while (aux!= NULL){
        i = aux;
        aux = aux->prox;
        free (i);
    }
}

int main()
{
    freopen ("L4Q2.in", "r", stdin);
    freopen ("L4Q2.out", "w", stdout);

    int casos, n, m, contagemCasos =1;
    int numero, posicao;
    lista *aux;
    int i, j;

    scanf ("%d", &casos); //numero de casos
    do{
        scanf ("%d %d", &n, &m); //N e M

        vetor = (lista**) malloc (m*sizeof (lista*));
        for (i=0; i<m; i++){ //atenção para o tempo de execução
            vetor [i] = NULL;
        }


        while (n>0){ //insere as entradas
            scanf ("%d", &numero);

            //insere numero
            posicao = numero%m;
            insere (numero, posicao);

            n--;
        }
        //scanf ("%d", ); coletar o 0

        if (contagemCasos != 1){
        //imprime a saida
        printf ("\n\nCaso %d:\n", contagemCasos);
        for (j =m; m>0; m--){
            for (aux = vetor [m-1]; aux!= NULL; aux = aux->prox){
                    if (aux->prox == NULL && m-1 == 0)
                        printf ("%d", aux->numero);
                    else
                        printf ("%d ", aux->numero);
            }
        }
        contagemCasos++;
        }
        else{
        printf ("Caso %d:\n", contagemCasos);
        for (j =m; m>0; m--){
            for (aux = vetor [m-1]; aux!= NULL; aux = aux->prox){
                    if (aux->prox == NULL && m-1 == 0)
                        printf ("%d", aux->numero);
                    else
                        printf ("%d ", aux->numero);
            }
        }
        }
        contagemCasos++;

        //libera o vetor
        for (i=0; i<j; i++){ //atenção para o tempo de execução
            liberaLista (vetor [i]);
        }
        free (vetor);

        casos--;
    }while (casos>0);

    return 0;
}
