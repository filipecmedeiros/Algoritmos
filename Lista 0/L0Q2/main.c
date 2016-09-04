#include <stdio.h>
#include <stdlib.h>

int main()
{
    freopen ("L0Q2.in", "r", stdin);
    freopen ("L0Q2.out", "w", stdout);

    int n, caso, hora, minuto, segundo, i, j, aux;
    int vertical [6][3], horizontal [3][6];

    caso=1;
    printf ("%d ", caso);
    for (scanf("%d", &n); n>0; n--){
        scanf ("%d:%d:%d", &hora, &minuto, &segundo);

        aux = hora;
        for (j=0; j<3; j++){
            if (j==1)
                aux = minuto;
            else if (j==2)
                aux = segundo;

            for (i=5; i>=0; i--){
                vertical [i][j] = aux%2;
                aux = aux/2;
            }
        }

        aux = hora;
        for (i=0; i<3; i++){
            if (i==1)
                aux = minuto;
            else if (i==2)
                aux = segundo;

            for (j=5; j>=0; j--){
                horizontal [i][j] = aux%2;
                aux = aux/2;
            }
        }

        //imprimir saida
        if (caso != 1)
            printf ("\n%d ", caso);

        caso++;
        for (i=0; i<6; i++){
            for (j=0; j<3; j++){
                printf ("%d", vertical [i][j]);
            }
        }
        printf (" ");
        for (i=0; i<3; i++){
            for (j=0; j<6; j++){
                printf ("%d", horizontal [i][j]);
            }
        }
    }

    return 0;
}
