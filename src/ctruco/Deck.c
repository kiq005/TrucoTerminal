/**************
 * Constantes *
 **************/
#define _NUM_CARTAS 40
/*************
 * Atributos *
 *************/
var(public, Object*, deck);
var(public, int, topo);
/**********
 * Classe *
 **********/
class(Deck, {&deck, &topo});// <-- Deve implementar a interface "PuxaCarta"
/**************
 * Construtor *
 **************/
constructor(Deck, 
	get(deck) = malloc(sizeof(int)*_NUM_CARTAS);
	call(&this, fazerMonte);
	);
/***********
 * Funções *
 ***********/
/*
 * Deck:fazerMonte - 
 * Cria o monte e embaralha.
 */
function(Deck, public, fazerMonte,
	call(&this, criaDeck);
	call(&this, embaralha);
	);
/*
 * Deck:criaDeck - 
 * Cria o monte de cartas em ordem crescente de valor
 */
function(Deck, public, criaDeck,
	int v, n;
	//puts("<< GRANDE POTENCIAL DE ERRO 1 >>");
	get(topo) = (generic)(intptr_t)_NUM_CARTAS -1;
	for(v=0;v<10;v++){
		for(n=0; n<4; n++){
			instanciate(Carta, nova_carta, v, n);
			((Object*)get(deck))[v*4+n] = *nova_carta;
			//printf("Carta: %s\n", (char*)call(&((Object*)get(deck))[v*4+n], Desenho));
		}
	}
	);
/*
 * Deck:sorteia - 
 * Recebe um int n, e retorna um generic int sortiado entre 0 e n.
 */
function(Deck, public, sorteia, 
	arg(int, n);
	return (generic)(intptr_t)(int)(rand()%n);
	);
/*
 * Deck:embaralha - 
 * Embaralha o monte.
 */
function(Deck, public, embaralha,
	Object aux;
	int sort, i;
	//puts("<< GRANDE POTENCIAL DE ERRO 2 >>");
	for(i=0; i<_NUM_CARTAS; i++){
		sort = (int)(intptr_t)call(&this, sorteia, _NUM_CARTAS -1);
		aux = ((Object*)get(deck))[sort];
		((Object*)get(deck))[sort] = ((Object*)get(deck))[_NUM_CARTAS -i -1];
		((Object*)get(deck))[_NUM_CARTAS -i -1] = aux;
	}
	);
/*
 * Deck:imprimeDeck - 
 * Imprime o monte
 */
function(Deck, public, imprimeDeck,
	int i;
	for(i=0; i<_NUM_CARTAS; i++){
		printf("%s", (char*)call(&((Object*)get(deck))[i], Desenho));
	}
	);
/*
 * Deck:obterCarta - 
 * Retira a carta do topo do monte
 */
////// OVERRIDE de interface!!!
function(Deck, public, obterCarta,
	Object *c;
	c = &((Object*)get(deck))[(int)(intptr_t)get(topo)];
	get(topo)--;
	return (generic)c;
	);