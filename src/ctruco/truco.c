#include <time.h>
#include "../c-poo/oo.h"
#include "PuxaCarta.c"
#include "Carta.c"
#include "Deck.c"
#include "Mesa.c"
#include "Jogador.c"
#include "J_IA1.c"
#include "J_Humano.c"
#include "Jogo.c"
/**********************
 * Inicio do Programa *
 **********************/
int main(void){
	/* Chama srand para uso de números aleatorios no jogo */
	srand(time(NULL));
	/* Instancia jogo e jogadores */
	instanciate(Jogo, jogo, 2);
	instanciate(J_Humano, j1);
	instanciate(J_IA1, j2);
	/* Adiciona jogadores ao jogo */
	call(jogo, addJogador, j1);
	call(jogo, addJogador, j2);
	/* Inicia o jogo */
	call(jogo, iniciar);
	
	return 0;
}