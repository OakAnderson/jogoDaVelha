#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"
#include "IA.h"


typedef struct tabuleiro
{
    int matriz[3][3];
    int jogadas[9];
}Tabuleiro;


int tab_recupera( Tabuleiro tab1, int num, int turno ){
    FILE* arquivo;
    char* arquivo_nome = "IPC.dat";
    Tabuleiro tab2, tab3;

    if( num != 0 ){
        tab_copia( tab1, &tab3 );
        jogaO( &tab3, num, turno );
    }

    arquivo = fopen( arquivo_nome, "rb" );

    if( arquivo == NULL ){
        printf("Impossível abrir o arquivo.\n");
        exit(1);
    }

    fread( &tab2, sizeof(Tabuleiro), 1, arquivo );
    while( !feof( arquivo ) ){
        //sleep(1);
        if( tab_compara( tab3, tab2 ) ){
            fclose( arquivo );
            return 1;        
        }
        fread( &tab2, sizeof(Tabuleiro), 1, arquivo );
    }

    fclose( arquivo );

    return 0;
}


void tab_copia( Tabuleiro tab1, Tabuleiro* tab2 ){
    for( int i = 0; i < 3; i++ ){
        for( int j = 0; j < 3; j++ ){
            tab2->matriz[i][j] = tab1.matriz[i][j];
            tab2->jogadas[i*3+j] = tab1.jogadas[i*3+j];
        }   
    }
}

// tab1 é o tabuleiro atual, tab2 é o recuperado dos dados
int tab_compara( Tabuleiro tab1, Tabuleiro tab2 ){
    int i = 0, igual;
    igual = 0;


    while (tab1.jogadas[i] != 0  ){
        if( tab2.jogadas[i] == 0 ){
            return 0;
        } else if( tab1.jogadas[i] != tab2.jogadas[i] ){
            return 0;
        }

        i++;
    }

    if( tab2.jogadas[i+1] == 0 ){
        return 1;    
    }

    return 0;
}


void tab_mostra_jogadas( Tabuleiro tab ){
    for( int i = 0; i < 9; i++ ){
        printf("%d -> ", tab.jogadas[i]);
    }
    printf("\n");
}


int IPC( Tabuleiro* tab, int turno ){
    int i, j, x, y, index;
    int jogadas[9] = {1,2,3,4,5,6,7,8,9};
    int sequencia[9];

    for( i = 9, j = 0; i > 0; i--, j++ ){
        index = rand() % i;
        sequencia[j] = jogadas[index];
        if( index != i-1 ){
            jogadas[index] = jogadas[i-1];
        }
    }

    for( i = 0; i < 9; i++ ){
        tab_acessa( sequencia[i], &x, &y );
        if( tab->matriz[x][y] == 0 ){
            if( turno >= 3 ){
                if( !tab_recupera( *tab, sequencia[i], turno ) ){
                    return sequencia[i];
                }
            } else {
                return sequencia[i];
            }
        }
    }

    for( i = 0; i < 9; i++ ){
        tab_acessa( sequencia[i], &x, &y );
        if( tab->matriz[x][y] == 0 ){
            return sequencia[i];
        }
    }
}