/* TAD: Inteligência Artificial para o Jogo da Velha */

typedef struct tabuleiro Tabuleiro;

int IPC(Tabuleiro*, int);


/* Função recupera tabuleiro
** Operação que compara o jogo atual com jogos antigos
*/
int tab_recupera( Tabuleiro, int, int );


/* Função compara
** Operação que retorna 1 se dois jogos forem iguais a menos de uma jogada
*/
int tab_compara( Tabuleiro, Tabuleiro );


void tab_copia( Tabuleiro, Tabuleiro* );
void tab_mostra_jogadas(Tabuleiro);