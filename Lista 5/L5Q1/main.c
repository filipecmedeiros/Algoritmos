//L5Q1 de fcma
#include <stdio.h>
#include <stdlib.h>

/*Salvar as coordenadas da porta, chave e baú*/
typedef struct Ponto{
    int linha;
    int coluna;
}Ponto;

/*Estrutura para a fila*/
typedef struct no{
    int linha;
    int coluna;
    struct no *prox;
}no;

typedef struct Fila{
    no *inicio;
    no *fim;
}Fila;

char mapa [1000][1000];
int distancia [1000][1000];
char cor [1000][1000];
Fila *fila;
int linhas, colunas;

/*A função insere uma posição ao final da fila*/
void f_insere_fila (int linha, int coluna){
    no *aux;

    aux = (no*) malloc (sizeof (no));

    if (aux != NULL){
        aux->linha = linha;
        aux->coluna = coluna;
        aux->prox = NULL;
    }

    if (fila->inicio == NULL){ //fila vazia
        fila->inicio = aux;
        fila->fim = aux;
    }
    else{
        fila->fim->prox = aux;
        fila->fim = aux;
    }
}

/*A função retira e retorna a primeira posição da fila*/
no* f_remove_fila (){
    no *aux;

    aux = fila->inicio;

    if (aux != NULL){
        fila->inicio = fila->inicio->prox;
        aux->prox = NULL;
    }

    return aux;
}

/*A função faz a busca em largura atualizando a distancia para o vertice inicial*/
void busca_largura (Ponto s){
    no* aux;

    cor [s.linha][s.coluna] = 'c'; //cinza
    distancia [s.linha][s.coluna] = 0;

    f_insere_fila(s.linha, s.coluna);

    while (fila->inicio != NULL){
        aux = f_remove_fila();

        if (mapa [aux->linha][aux->coluna] != '#'){
            if (aux->linha > 0){
                if (cor [aux->linha-1][aux->coluna] == 'b'){
                    cor [aux->linha-1][aux->coluna] = 'c';
                    distancia [aux->linha-1][aux->coluna] = distancia [aux->linha][aux->coluna] + 1;
                    f_insere_fila (aux->linha-1, aux->coluna);
                }
            }
            if (aux->linha < linhas){
                if (cor [aux->linha+1][aux->coluna] == 'b'){
                    cor [aux->linha+1][aux->coluna] = 'c';
                    distancia [aux->linha+1][aux->coluna] = distancia [aux->linha][aux->coluna] + 1;
                    f_insere_fila (aux->linha+1, aux->coluna);
                }
            }
            if (aux->coluna > 0){
                if (cor [aux->linha][aux->coluna-1] == 'b'){
                    cor [aux->linha][aux->coluna-1] = 'c';
                    distancia [aux->linha][aux->coluna-1] = distancia [aux->linha][aux->coluna] + 1;
                    f_insere_fila (aux->linha, aux->coluna-1);
                }
            }
            if (aux->coluna < colunas){
                if (cor [aux->linha][aux->coluna+1] == 'b'){
                    cor [aux->linha][aux->coluna+1] = 'c';
                    distancia [aux->linha][aux->coluna+1] = distancia [aux->linha][aux->coluna] + 1;
                    f_insere_fila (aux->linha, aux->coluna+1);
                }
            }
        }
        cor [aux->linha][aux->coluna] = 'p'; //preto
    }
}

//debug
void f_imprime_entrada (){
    int i, j;

    for (i=0; i<linhas; i++){
        for (j=0; j<colunas; j++){
            printf ("%c", mapa[i][j]);
        }
        printf ("\n");
    }

    for (i=0; i<linhas; i++){
        for (j=0; j<colunas; j++){
            printf ("%d", distancia[i][j]);
        }
        printf ("\n");
    }

    for (i=0; i<linhas; i++){
        for (j=0; j<colunas; j++){
            printf ("%c", cor[i][j]);
        }
        printf ("\n");
    }
}

void f_limpa_matriz (){
    int i, j;

    for (i=0; i<linhas; i++){
        for (j=0; j<colunas; j++){
            distancia [i][j] = -1;  //# ou .
            cor [i][j] = 'b'; //branco
        }
    }
}

int main()
{
    freopen ("L5Q1.in", "r", stdin);
    freopen ("L5Q1.out", "w", stdout);

    int casos, contadorCasos = 1, distanciaTotal, respiracao;
    int i, j;
    char lixo;
    Ponto p, c, b; //as coordenadas da porta, chave e baú respectivamente

    fila = (Fila*) malloc (sizeof (Fila)); //inicializa a fila
    fila->inicio = fila->fim = NULL;

    scanf ("%d", &casos); //numero de casos

    while (casos > 0){
        scanf ("%d %d", &linhas, &colunas); //numero de linhas e colunas do mapa

        scanf ("%c", &lixo); //coleta o \n

        for (i=0; i<linhas; i++){ //coleta o mapa, inicializa a distancia e a cor e salva os pontos
            for (j=0; j<colunas; j++){
                scanf ("%c", &mapa[i][j]);

                switch (mapa [i][j]){

                    case 'P':   p.linha = i; //salvar porta
                                p.coluna = j;
                                distancia [i][j] = -1;
                                cor [i][j] = 'b'; //branco
                        break;

                    case 'C':   c.linha = i; //salvar chave
                                c.coluna = j;
                                distancia [i][j] = -1;
                                cor [i][j] = 'b'; //branco
                        break;

                    case 'B':   b.linha = i; //salvar baú
                                b.coluna = j;
                                distancia [i][j] = -1;
                                cor [i][j] = 'b'; //branco
                        break;

                    default:    distancia [i][j] = -1;  //# ou .
                                cor [i][j] = 'b'; //branco
                            break;
                }
            }
            scanf ("%c", &lixo); //coleta o \n
        }
        scanf ("%d", &respiracao);

        busca_largura(p);

        if (distancia [c.linha][c.coluna] == -1 || distancia [b.linha][b.coluna] == -1){
            distanciaTotal = -1;
        }
        else{
            distanciaTotal = distancia [c.linha][c.coluna] + distancia [b.linha][b.coluna];

            f_limpa_matriz();

            busca_largura(c);
            distanciaTotal = distanciaTotal + distancia [b.linha][b.coluna];

            if (respiracao < distanciaTotal){
                distanciaTotal = distanciaTotal*2;
            }
        }


        //imprimir saida
        printf ("Caso #%d: %d\n", contadorCasos, distanciaTotal);
        contadorCasos++;
        casos--;
    }

    return 0;
}
