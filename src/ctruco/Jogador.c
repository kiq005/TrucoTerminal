
/*************
 * Atributos *
 *************/
var(public, Object*, mao);
var(public, int, cartas);

/**********
 * Classe *
 **********/
class(Jogador, {&mao, &cartas});

/**************
 * Construtor *
 **************/
constructor(Jogador,
	instanciate(Carta, c1, _CNONE, _NONAIPE);
	instanciate(Carta, c2, _CNONE, _NONAIPE);
	instanciate(Carta, c3, _CNONE, _NONAIPE);
	get(cartas) = (generic)(intptr_t)0;
	get(mao) = (generic)malloc(sizeof(Object)*3);

	((Object*)get(mao))[0] = *c1;
	((Object*)get(mao))[1] = *c2;
	((Object*)get(mao))[2] = *c3;
	);

/***********
 * Funções *
 ***********/
/*
 * Jogador:darCarta - 
 * Recebe um Object* com tipo Carta, e coloca na mão do jogador
 */
function(Jogador, public, darCarta,
	arg(Object*, c);
	int n, v, num_cartas;
	v = (int)(intptr_t)call(c, getValor);
	n = (int)(intptr_t)call(c, getNaipe);
	num_cartas = (int)(intptr_t)get(cartas);
	call(&((Object*)get(mao))[num_cartas], setValor, v);
	call(&((Object*)get(mao))[num_cartas], setNaipe, n);
	get(cartas) = (generic)(intptr_t)(((int)(intptr_t)get(cartas))+1);
	);
/*
 * Jogador:esvaziarMao - 
 * Esvazia a mão do jogador
 */
function(Jogador, public, esvaziarMao,
	get(cartas) = (generic)(intptr_t)0;
	);
/*
 * Jogador:organizaMao - 
 * Organiza mão do jogador, mantendo as cartas sempre a esquerda
 */
function(Jogador, public, organizaMao,
	//printf("<< Organizando: [%s] [%s] [%s] >>\n", (char*)call(&((Object*)get(mao))[0], Desenho), (char*)call(&((Object*)get(mao))[1], Desenho), (char*)call(&((Object*)get(mao))[2], Desenho));
	if( (int)(intptr_t)call(&((Object*)get(mao))[0], getValor) == _CNONE){
		//puts("<Primeira vazia>");
		if( (int)(intptr_t)call(&((Object*)get(mao))[2], getValor) != _CNONE){
			int v, n;
			//puts("<Trocando pela ultima>");
			v = (int)(intptr_t)call(&((Object*)get(mao))[2], getValor);
			n = (int)(intptr_t)call(&((Object*)get(mao))[2], getNaipe);
			call(&((Object*)get(mao))[0], setValor, v);
			call(&((Object*)get(mao))[0], setNaipe, n);
			call(&((Object*)get(mao))[2], nulificar);
		}
		else if((int)(intptr_t)call(&((Object*)get(mao))[1], getValor) != _CNONE){
			int v, n;
			//puts("<Trocando pela segunda>");
			v = (int)(intptr_t)call(&((Object*)get(mao))[1], getValor);
			n = (int)(intptr_t)call(&((Object*)get(mao))[1], getNaipe);
			call(&((Object*)get(mao))[0], setValor, v);
			call(&((Object*)get(mao))[0], setNaipe, n);
			call(&((Object*)get(mao))[1], nulificar);
		}
		else{

		}
	}
	else if( (int)(intptr_t)call(&((Object*)get(mao))[1], getValor) == _CNONE){
		//puts("<Segunda vazia>");
		if( (int)(intptr_t)call(&((Object*)get(mao))[2], getValor) != _CNONE){
			int v, n;
			//puts("<Trocando pela ultima>");
			v = (int)(intptr_t)call(&((Object*)get(mao))[2], getValor);
			n = (int)(intptr_t)call(&((Object*)get(mao))[2], getNaipe);
			call(&((Object*)get(mao))[1], setValor, v);
			call(&((Object*)get(mao))[1], setNaipe, n);
			call(&((Object*)get(mao))[2], nulificar);
		}
	}
	else{
		//puts("<Terceira vazia>");
	}
	//printf("<< Organizado: [%s] [%s] [%s] >>\n", (char*)call(&((Object*)get(mao))[0], Desenho), (char*)call(&((Object*)get(mao))[1], Desenho), (char*)call(&((Object*)get(mao))[2], Desenho));
	);
function(Jogador, public, obterCarta,
	fprintf(stderr, "Erro: Função 'obterCarta' não implementada.");
	);