/*L2Q1 de fcma*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Chave{
    char nome [16];
    int existe;
}chave;


 chave *hash;

/*A função calcula o hash code a partir de uma string*/
int f_hashCode (char nome [16]){
    int hashCode, i;

    for (i=0; nome[i]!= '\0'; i++){
        hashCode = hashCode + (nome[i]*(i+1));
    }

    hashCode = (hashCode*19)%101;

    return hashCode;
}

/*A função calcula o novo hash code através do endereçamento aberto por double hashing*/
int f_colisao (int hashCode, int j){
    int colisao;

    colisao = (hashCode + (j*j) + (23*j))%101;

    return colisao;
}

/*A função faz uma inserção em um hash*/
int insercao (char nome [16]){
    int result = 0, hashCode, colisao, j;

    hashCode = f_hashCode(nome); //calcula o hash code

    if (hash [hashCode].existe == 0){ //local vago
        strcpy (hash [hashCode].nome, nome);
        hash[hashCode].existe = 1;
        result = 1;
    }
    else{ //local ocupado
        if (strcmp (hash[hashCode].nome, nome) != 0){ //evitar chave duplicada

            //colisao
            for (j=1; j<20 && result == 0; j++){

                colisao = f_colisao (hashCode, j);

                if (hash[colisao].existe == 0){ //local vago
                    strcpy (hash [colisao].nome, nome);
                    hash[hashCode].existe = 1;
                    result = 1;
                }
                else{
                    if (strcmp (hash[colisao].nome, nome) == 0){
                        result = 0;
                    }
                }
            }
        }
    }


    return result;
}

/*A função procura por uma chave e elimina, caso exista*/
int remover (char nome [16]){
    int result = 0, hashCode, colisao, j;

    hashCode = f_hashCode(nome);//calcula o hash code

    if (hash [hashCode].existe == 1){ //se tiver alguma string no local, verificar

        if (strcmp (hash[hashCode].nome, nome) == 0){ //se for o mesmo nome, achou
            hash [hashCode].existe = 0; //remover string
            result = 1;
        }
        //possivel colisao
        for (j=1; j<20 && result == 0; j++){

            colisao = f_colisao (hashCode, j);

            if (hash[colisao].existe == 1){
                if (strcmp (hash[colisao].nome, nome) == 0){ //se for o mesmo nome, achou
                    hash [colisao].existe = 0;//remover string
                    result = 1;
                }
            }
        }
    }
    else{ //verificar se elemento anterior foi removido
        for (j=1; j<20 && result == 0; j++){

            colisao = f_colisao (hashCode, j);

            if (hash[colisao].existe == 1){
                if (strcmp (hash[colisao].nome, nome) == 0){ //se for o mesmo nome, achou
                    hash [colisao].existe = 0;//remover string
                    result = 1;
                }
            }
        }
    }

    return result;
}

int main()
{
    freopen ("L2Q1.in", "r", stdin);
    freopen ("L2Q1.out", "w", stdout);

    int casos, operacoes, i, n;
    char funct [5], nome [16];

    scanf ("%d", &casos);
    for ( ; casos>0; casos--){

        hash = (chave*) malloc (101*sizeof (chave)); //aloca espaço para a tabela hash

        n=0;
        scanf ("%d", &operacoes);
        for ( ; operacoes>0; operacoes--){
            scanf ("%4[^\n]s:%s", funct, nome);
            //scanf ("%3s");
            //scanf ("%s", nome);
            //printf ("%s:%s\n", funct, nome);
            //printf ("aqui\n");
            switch (funct [0]){
                case 'A': if (insercao(nome)==1);
                            n++;
                        break;

                case 'D':if (remover (nome)==1);
                            n--;
                        break;
            }

        }

        printf ("%d\n", n);
        for (i=0; i<101; i++){//imprimir saida

            if (hash[i].existe == 1){
                printf ("%d:%s\n", i, hash [i].nome);
                n--;
            }

        }

        free (hash);
    }

    return 0;
}
