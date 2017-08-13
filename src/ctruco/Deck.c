/* Constantes sobre definição */
#define _NUM_CARTAS 40
/* Atributos */
var(public, Object*, deck);
var(public, int, topo);
/* Classe */
class(Deck, {&deck, &topo});// <-- Deve implementar a interface "PuxaCarta"
/* Construtor */
constructor(Deck, 
	get(deck) = malloc(sizeof(int)*_NUM_CARTAS);
	call(&this, fazerMonte);
	);
/* Métodos */
function(Deck, public, fazerMonte,
	call(&this, criaDeck);
	call(&this, embaralha);
	);
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
function(Deck, public, sorteia, 
	arg(int, n);
	return (generic)(intptr_t)(int)(rand()%n);
	);
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

function(Deck, public, imprimeDeck,
	int i;
	for(i=0; i<_NUM_CARTAS; i++){
		printf("%s", (char*)call(&((Object*)get(deck))[i], Desenho));
	}
	);

////// OVERRIDE de interface!!!
function(Deck, public, obterCarta,
	Object *c;
	c = &((Object*)get(deck))[(int)(intptr_t)get(topo)];
	get(topo)--;
	return (generic)c;
	);