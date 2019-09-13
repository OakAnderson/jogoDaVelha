#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"

typedef struct tabuleiro {
    int matriz[3][3];
} Tabuleiro;


Tabuleiro tab_novo( void ){
    Tabuleiro novo;

    for( int i = 0; i < 3; i++ ){
        for( int j = 0; j < 3; j++ ){
            novo.matriz[i][j] = 0;
        }
    }

    return novo;
}


void tab_mostra( Tabuleiro* tab, int jogador ){
    int i, j;
    system("clear");

    if( jogador == 1 ){
        printf("\t Jogador X\n");
    } else {
        printf("\t Jogador O\n");
    }

    for( i = 0; i < 3; i++ ){
        printf("\t");
        for( j = 0; j < 3; j++ ){
            if( tab->matriz[i][j] == 0 ){
                printf("   ");
            } else if ( tab->matriz[i][j] == 1 ){
                printf(" X ");
            } else {
                printf(" O ");
            }
            if( j < 2 ){
                printf("|");
            }
        }
        if( i < 2 ){
            printf("\t\t %d | %d | %d", ((2-i)*3)+1, ((2-i)*3)+2, ((2-i)*3)+3);
            printf("\n\t-----------");
            printf("\t\t-----------\n");
        } else {
            printf("\t\t %d | %d | %d", ((2-i)*3)+1, ((2-i)*3)+2, ((2-i)*3)+3);
            printf("\n");
        }
    }
}


void tab_acessa( int num, int *x, int *y ){
    num--;

    *x = 2 - num/3;
    *y = (num % 3);
}


void jogaX( Tabuleiro* tab, int num ){
    int x, y;

    tab_acessa( num, &x, &y );
    
    tab->matriz[x][y] = 1;
}


void jogaO( Tabuleiro* tab, int num ){
    int x, y;
    
    tab_acessa(num, &x, &y);

    tab->matriz[x][y] = 2;
}


int val_campo( Tabuleiro* tab, int num ){
    int x, y;

    tab_acessa( num, &x, &y );

    if( tab->matriz[x][y] != 0 ){
        return 0;
    }

    return 1;
}


int val_ganhador( Tabuleiro* tab ){
    int num;

    if( tab->matriz[1][1] != 0 ){
        num = tab->matriz[1][1];

        if( tab->matriz[0][0] == num && tab->matriz[2][2] == num ){
            return 1;
        } else if ( tab->matriz[0][2] == num && tab->matriz[2][0] == num ){
            return 1;
        } else if ( tab->matriz[0][1] == num && tab->matriz[2][1] == num ){
            return 1;
        } else if ( tab->matriz[1][0] == num && tab->matriz[1][2] == num ){
            return 1;
        }
    }

    if( tab->matriz[0][0] != 0 ){
        num = tab->matriz[0][0];

        if( tab->matriz[0][1] == num && tab->matriz[0][2] == num ){
            return 1;
        } else if ( tab->matriz[1][0] == num && tab->matriz[2][0] == num ){
            return 1;
        }
    }

    if( tab->matriz[2][2] != 0 ){
        num = tab->matriz[2][2];

        if( tab->matriz[2][1] == num && tab->matriz[2][0] == num ){
            return 1;
        } else if ( tab->matriz[1][2] == num && tab->matriz[0][2] == num ){
            return 1;
        }
    }

    return 0;
}


int jogada( Tabuleiro* tab ){
    char num;
    int result;

    printf("Jogada: ");
    scanf(" %c", &num);

    if( !isdigit(num) ){
        printf("Campo inválido. Digite apenas números.\n");
        return jogada(tab);
    }

    result = num - '0';

    if( result > 9 || result < 1 ){
        printf("Digite apenas 1-9!\n");
        return jogada(tab);
    }

    if( !val_campo( tab , result) ){
        printf("Campo ocupado!\n");
        return jogada(tab);
    }
    
    return num-'0';
}


void inicia_jogo( void ){
    int num, vez, i, win;
    Tabuleiro tab;

    tab = tab_novo();

    for( i = 0; i < 9; i++ ){
        vez = i % 2;
        if( vez == 0 ){
            tab_mostra( &tab, 1 );
            num = jogada( &tab );
            jogaX( &tab, num );
        } else {
            tab_mostra( &tab, 2 );
            num = jogada( &tab );
            jogaO( &tab, num );
        }

        win = val_ganhador( &tab );
        if( win ){
            if( vez == 0 ){
                tab_mostra( &tab, 2 );
                printf("\nO jogador X venceu!\n");
                break;
            } else {
                tab_mostra( &tab, 1 );
                printf("\nO jogador O venceu!\n");
                break;
            }
        }
    }

    if( i == 8 && !win ){
        printf("\nEmpate!\n");
    }
}
