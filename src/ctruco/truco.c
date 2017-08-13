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

/* Constantes sobre definição */
/* Atributos */
/* Classe */
/* Construtor */
/* Métodos */

main(void){
	srand(time(NULL));

	instanciate(Jogo, jogo, 2);
	instanciate(J_Humano, j1);
	instanciate(J_IA1, j2);

	call(jogo, addJogador, j1);
	call(jogo, addJogador, j2);
	call(jogo, iniciar);
	return 0;
}