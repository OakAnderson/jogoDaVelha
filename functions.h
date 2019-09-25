/* TAD: Jogo da Velha */

typedef struct tabuleiro Tabuleiro;


/* Função salva tabuleiro
** Operação que salva em arquivo binário uma partida
*/
void tab_salva( Tabuleiro* );


/* Função tabuleiro novo
** Operação que limpa o tabuleiro
*/
Tabuleiro tab_novo( void );


/* Função mostra tabuleiro
** Operação que mostra o tabuleiro na tela (1 para X, 2 para O
** e 0 para vazio)
*/
void tab_mostra( Tabuleiro*, int );


/* Função acessa tabuleiro
** Operação que a partir de um número, salva em duas variáveis
** a coluna e a linha daquele valor
*/
void tab_acessa( int, int*, int* );


/* Função jogador X
** Operação que recebe uma posição do tabuleiro e marca com X
*/
void jogaX( Tabuleiro*, int, int );


/* Função jogador O
** Operação que recebe uma posição do tabuleiro e marca com O
*/
void jogaO( Tabuleiro*, int, int );


/* Função valida campo
** Operação que retorna se o campo escolhido está vazio ou não
*/
int val_campo( Tabuleiro*, int );


/* Função valida ganhador
** Operação que verifica se alguém ganhou
*/
int val_ganhador( Tabuleiro* );


/* Função jogada
** Operação que inicia uma jogada recebendo o campo escolhido
** do usuário, retorna o campo
*/
int jogada( Tabuleiro* );


/* Função inicia jogo
** Operação que faz o loop da rotina do jogo
*/
void inicia_jogo( int );


/* Função menu principal
** Operação que incia o programa pelo menu principal
*/
void menuPrincipal( void );