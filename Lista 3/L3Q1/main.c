//L3Q1 @fcma
#include <stdio.h>
#include <stdlib.h>

typedef struct Estrela{ //lista encadeada com ponteiro para o representante
    float x;
    float y;
    struct Estrela *prox;
    struct Estrela *representante;
}estrela;

typedef struct Constelacao { //conjunto disjunto por lista encadeada
    estrela *inicio;
    estrela *fim;
}constelacao;


estrela make_set (float x, float y){
    estrela *novo;

    novo = malloc (sizeof (estrela));

    novo->x = x;
    novo->y = y;

    novo->prox = NULL;
    novo->representante = &novo;

    return &novo;
}



int main()
{
    freopen ("L3Q1.in", "r", stdin);
    //freopen ("L3Q1.out", "w", stdout);

    int testes, caso=1;
    int nEstrelas, i;
    float distancia, x, y;
    constelacao *vetor; //um vetor de conjuntos disjuntos

    scanf ("%d", &testes); //numero de casos
    while (testes > 0){

        scanf ("%d", &nEstrelas); //numero de estrelas pro caso
        scanf ("%f", &distancia); //distancia minima

        vetor = malloc (nEstrelas*sizeof (constelacao));

        for (i=0; i<nEstrelas; i++){
            scanf ("%f", &x);
            scanf ("%f", &y);
            vetor[i]->inicio = make_set(x, y);
            vetor [i].inicio = vetor[i].fim; //apontam pro mesmo elemento

            printf ("X=%.2f\nY=%.2f\nInicio=%dznFim=%d\n", vetor[i]->inicio->x, vetor[i]->inicio->y, vetor[i].inicio, vetor[i].fim);
        }





        testes--;
    }

    return 0;
}
