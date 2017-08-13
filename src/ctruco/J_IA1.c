/* Atributos */

/* Classe */
extends(J_IA1, Jogador, {});
/* Construtor */
// ??? - Esperar verificações

/* Métodos */
function(J_IA1, public, obterCarta, // Override!
	int selecao, n, v;
	instanciate(Carta, carta);
	puts("<< Obtendo carta IA >>");
	if((int)(intptr_t)(get(cartas))<1){
		puts("<< IA Não tem cartas!!! >>");
		return NULL;
	}
	selecao = (int) rand()%(int)(intptr_t)(get(cartas));// Verificar se IA joga a ultima carta?
	n = (int)(intptr_t)call( &((Object*)get(mao))[selecao], getNaipe);
	v = (int)(intptr_t)call( &((Object*)get(mao))[selecao], getValor);
	call(carta, setNaipe, n);
	call(carta, setValor, v);
	//c = &((Object*)get(mao))[selecao];

	call(&((Object*)get(mao))[selecao], nulificar);//((Object*)get(mao))[selecao]._type = NULL;
	//get(cartas) = (generic)(intptr_t)(((int)(intptr_t)get(cartas))-1);// <-- Deve sofrer mudança
	get(cartas)--;
	call(&this, organizaMao);// Chamada para super!
	printf("IA jogou carta: %s\n", (char*)call(carta, Desenho));
	return (generic)carta;
	);