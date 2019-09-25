#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"
#include "IA.h"

typedef struct tabuleiro {
    int matriz[3][3];
    int jogadas[9];
} Tabuleiro;


void tab_salva( Tabuleiro* tab ){
    FILE* arquivo;
    char* arquivo_nome = "IPC.dat";

    arquivo = fopen( arquivo_nome, "ab" );

    if( arquivo == NULL ){
        arquivo = fopen( arquivo_nome, "wb" );
    }

    if( arquivo == NULL ){
        printf("Não foi possível abrir o arquivo.\n");
    }
    if( !tab_recupera( *tab, 0, 0 ) ){
        fwrite( tab, sizeof(Tabuleiro), 1, arquivo );
    }
    fclose(arquivo);
}


int randPcTurn( Tabuleiro* tab ){
    int num, i, j;

    num = rand() % 10;
    if( num == 0 ){
        return randPcTurn( tab );
    }

    tab_acessa( num, &i, &j );
    if( tab->matriz[i][j] != 0 ){
        return randPcTurn( tab );
    }

    return num;
}


Tabuleiro tab_novo( void ){
    Tabuleiro novo;

    for( int i = 0; i < 3; i++ ){
        for( int j = 0; j < 3; j++ ){
            novo.matriz[i][j] = 0;
            novo.jogadas[i*3 + j] = 0;
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


void tab_acessa( int num, int *i, int *j ){
    num--;

    *i = 2 - num/3;
    *j = (num % 3);
}


void jogaX( Tabuleiro* tab, int num, int turno ){
    int i, j;

    tab_acessa( num, &i, &j );
    
    tab->matriz[i][j] = 1;
    tab->jogadas[turno] = num;
}


void jogaO( Tabuleiro* tab, int num, int turno ){
    int i, j;
    
    tab_acessa(num, &i, &j);

    tab->matriz[i][j] = 2;
    tab->jogadas[turno] = num;
}


int val_campo( Tabuleiro* tab, int num ){
    int i, j;

    tab_acessa( num, &i, &j );

    if( tab->matriz[i][j] != 0 ){
        return 0;
    }

    return 1;
}


int val_ganhador( Tabuleiro* tab ){
    int num;

    for( int i = 0; i < 3; i++ ){
        if( tab->matriz[i][0] != 0 && (tab->matriz[i][0] == tab->matriz[i][1] && tab->matriz[i][1] == tab->matriz[i][2]) ){
            return 1;
        }
    }

    for( int i = 0; i < 3; i++ ){
        if( tab->matriz[0][i] != 0 && (tab->matriz[0][i] == tab->matriz[1][i] && tab->matriz[1][i] == tab->matriz[2][i]) ){
            return 1;
        }
    }

    if( tab->matriz[0][0] != 0 && (tab->matriz[0][0] == tab->matriz[1][1] && tab->matriz[1][1] == tab->matriz[2][2]) )
        return 1;
    if( tab->matriz[0][2] != 0 && (tab->matriz[0][2] == tab->matriz[1][1] && tab->matriz[1][1] == tab->matriz[2][0]) )
        return 1;

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


int inicia_jogoPCvsPC( int n ){
    int num, vez, i, win;
    Tabuleiro tab;

    srand(time(NULL));
    tab = tab_novo();

    for( i = 0; i < 9; i++ ){
        vez = i % 2;
        if( vez == 0 ){
            //tab_mostra( &tab, 1 );
            num = randPcTurn( &tab );
            //num = jogada( &tab );
            jogaX( &tab, num, i );
        } else {
            //tab_mostra( &tab, 2 );
            if( n == 2 )
                num = IPC( &tab, i );
            else
                num = jogada( &tab );
            jogaO( &tab, num, i );
        }

        win = val_ganhador( &tab );
        if( win ){
            if( vez == 0 ){
                //tab_mostra( &tab, 2 );
                //printf("\nO jogador X venceu!\n");
                tab_salva( &tab );
                return 0;
            } else {
                //tab_mostra( &tab, 1 );
                //printf("\nO jogador O venceu!\n");
                return 1;
            }
        }
    }

    if( i == 9 && !win ){
        //tab_mostra( &tab, 0 );
        //printf("\nEmpate!\n");
        return 2;
    }

    //printf("Atual:      ");
    //tab_mostra_jogadas(tab);
}

void inicia_jogo( int n ){
    int num, vez, i, win;
    Tabuleiro tab;

    srand(time(NULL));
    tab = tab_novo();

    for( i = 0; i < 9; i++ ){
        vez = i % 2;
        if( vez == 0 ){
            tab_mostra( &tab, 1 );
            //num = randPcTurn( &tab );
            num = jogada( &tab );
            jogaX( &tab, num, i );
        } else {
            tab_mostra( &tab, 2 );
            if( n == 2 )
                num = IPC( &tab, i );
            else
                num = jogada( &tab );
            jogaO( &tab, num, i );
        }

        win = val_ganhador( &tab );
        if( win ){
            if( vez == 0 ){
                tab_mostra( &tab, 2 );
                printf("\nO jogador X venceu!\n");
                tab_salva( &tab );
                break;
            } else {
                tab_mostra( &tab, 1 );
                printf("\nO jogador O venceu!\n");
                break;
            }
        }
    }

    if( i == 9 && !win ){
        tab_mostra( &tab, 0 );
        printf("\nEmpate!\n");
    }
}


void menuPrincipal( void ){
    char escolha, win, x=0, o=0, empate=0;

    system("clear");

    printf("1 - 2 jogadores\n2 - jogador vs computador\n3 - computador vs computador\n\n");
    printf("Escolha: ");
    scanf(" %c", &escolha);
    while( escolha != '1' && escolha != '2' && escolha != '3' ){
        system("clear");
        printf("1 - 2 jogadores\n2 - jogador vs computador\n3 - computador vs computador\n\n");
        printf("Insira apenas 1 ou 2!\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);
    }

    if( escolha == '3' ){
        for( float i = 0.0; i < 100000.0; i++ ){
            win = inicia_jogoPCvsPC(2);
            if( win == 0 ){
                x += 1;
            } else if( win == 1 ) {
                o += 1;
            } else {
                empate += 1;
            }
            system("clear");
            printf("%.2f %% \n", (i/100000.0)*100);
        }
    } else {
        inicia_jogo(escolha-'0');
    }

    printf("X ganhou %d vezes\nO ganhou %d vezes\n%d Empates\n", x, o, empate);

}
