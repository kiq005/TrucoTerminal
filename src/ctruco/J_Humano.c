/*************
 * Atributos *
 *************/
/**********
 * Classe *
 **********/
extends(J_Humano, Jogador, {});

/**************
 * Construtor *
 **************/

/***********
 * Funções *
 ***********/
/*
 * J_Humano:imprimeMao - 
 * Imprime a mão do jogador
 */
function(J_Humano, public, imprimeMao, 
	int i;
	for(i=0; i<(int)(intptr_t)get(cartas); i++){
		printf("%s ", (char*)call(&((Object*)get(mao))[i], Desenho));
	}
	printf("\n");
	);

/*
 * J_Humano:obterCarta - 
 * Solicita entrada do usuário, para decidir por uma carta, e retorna a 
 * carta solicitada em um generic Object.
 */
function(J_Humano, public, obterCarta, // Override!
	instanciate(Carta, carta)
	int c = 0, n, v;

	//puts("<< Obtendo carta Humano >>");
	while(c<1 || c>((int)(intptr_t)get(cartas)) ){
		printf("Qual carta deseja jogar?[1-%d]", (int)(intptr_t)get(cartas));
		call(&this, imprimeMao);
		scanf("%d", &c);// <-- Checar retorno???
	}
	n = (int)(intptr_t)call( &((Object*)get(mao))[c-1], getNaipe);
	v = (int)(intptr_t)call( &((Object*)get(mao))[c-1], getValor);
	call(carta, setNaipe, n);
	call(carta, setValor, v);
	call(&((Object*)get(mao))[c-1], nulificar);//((Object*)get(mao))[c-1]._type = NULL;
	get(cartas)--;
	call(&this, organizaMao);
	//printf("<< Jogando carta: %s>>\n", (char*)call(carta, Desenho));
	return carta;
	);