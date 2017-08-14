/*************
 * Atributos *
 *************/
var(public, Object, mesa);
var(public, Object, baralho);
var(public, Object*, jogadores);
var(public, int, emJogo);
var(public, int, proximo);
var(public, int, daCarta);

/**********
 * Classe *
 **********/
class(Jogo, {&mesa, &baralho, &jogadores, &emJogo, &proximo, &daCarta});

/*******************************************
 * Construtor -                            *
 * Recebe um int com o número de jogadores *
 *******************************************/
constructor(Jogo, 
	arg(int, num_jogadores);
	instanciate(Mesa, m);
	instanciate(Deck, b);
	get(mesa) = m;
	get(baralho) = b;
	get(jogadores) = (generic)malloc(sizeof(Object)*num_jogadores);
	get(emJogo) = (generic)(intptr_t)0;
	get(daCarta) = (generic)(intptr_t)0;
	get(proximo) = (generic)(intptr_t)0;
	);

/***********
 * Funções *
 ***********/
/*
 * Jogo:addJogador - 
 * Recebe um Object* do tipo Jogador, e o adiciona ao jogo
 */
function(Jogo, public, addJogador, 
	arg(Object*, j);
	((Object*)get(jogadores))[(int)(intptr_t)get(emJogo)] = *j;
	get(emJogo) = (generic)(intptr_t)((int)(intptr_t)get(emJogo)+1);
	);
/*
 * Jogo:distribuirCartas - 
 * Realiza a distribuição de cartas entre os jogadores
 */
function(Jogo, public, distribuirCartas,
	Object* c;
	int i, j;
	/* Faz a distribuição um a um */
	for(i=0; i<3;i++){
		for(j=0; j<(int)(intptr_t)get(emJogo); j++){
			c = call(((Object*)get(baralho)), obterCarta);
			call(&((Object*)get(jogadores))[j], darCarta, c);
			//printf("<< Dando carta: %s>>\n", (char*)call(c, Desenho));
		}
	}
	/* Vira a ultima carta */
	c = call(((Object*)get(baralho)), obterCarta);
	call((Object*)get(mesa), vira, c);
	);
/*
 * Jogo:verMaior - 
 * Recebe um Object* c, que é uma lista de cartas jogadas na mesa, e 
 * verifica qual foi a maior carta jogada, retornando sua posição em
 * um generic int.
 */
function(Jogo, public, verMaior, 
	arg(Object*, c);
	Object *m, *v;
	int maior = 0, disp, i;
	for(i=0; i<(int)(intptr_t)get(emJogo); i++){
		//puts("<<Vendo cartas em jogo >>");
		if(strcmp(c[i]._type->_name, "Carta")!=0)
			continue;
		if(call((Object*)get(mesa), getMaior) == NULL)
			call((Object*)get(mesa), setMaior, c[i]);
		if((int)(intptr_t)(call((Object*)call((Object*)get(mesa), getMaior), getValor) ) == (int)(intptr_t)call(&c[i], getValor) \
			&& (int)(intptr_t)(call((Object*)call((Object*)get(mesa), getMaior), getNaipe) ) == (int)(intptr_t)call(&c[i], getNaipe))
			continue;
		m = (Object*)call((Object*)get(mesa), getMaior);
		v = (Object*)call((Object*)get(mesa), getVira);
		//puts("<< Disputa >>");
		disp = (int)(intptr_t)call(&c[i], Ganha, m, v);
		if(disp==_GANHA){
			//puts("<< Ganha >>");
			maior = i;
			call((Object*)get(mesa), setMaior, &c[i]);
		}
		else if(disp==_EMPATA){
			//puts("<< Empata >>");
			maior = -1;
		}
		else{
			//puts("<< Perde >>");
		}
	}
	//puts("<< Retorno >>");
	return (generic)(intptr_t)maior;
	);
/*
 * Jogo:iniciar - 
 * Inicia e controla o jogo
 */
function(Jogo, public, iniciar,
	Object c[(int)(intptr_t)get(emJogo)];
	int maior = -1, turno, i, partida;
	//puts("<< Entrando no loop de jogo >>");
	while((int)(intptr_t)call((Object*)get(mesa), getTime1)<12 && (int)(intptr_t)call((Object*)get(mesa), getTime2)<12){
		/* Junta as cartas no monte */
		//puts("<< Juntando cartas >>");
		call((Object*)get(baralho), fazerMonte);
		/* Distribui as cartas */
		//puts("<< Distribuindo cartas >>");
		call(&this, distribuirCartas);
		/* Inicia a rodada */
		for(turno=0; turno<3;turno++){
			/* Cada jogador desce uma carta */
			//puts("<< Descendo cartas >>");
			for(i=0; i<(int)(intptr_t)get(emJogo);i++){
				//puts("<< Chamando imprime Mesa >>");
				call((Object*)get(mesa), imprimeMesa);
				//puts("<< Obtendo carta do jogador >>");
				c[(int)(intptr_t)get(proximo)] = *(Object*)call(&((Object*)get(jogadores))[(int)(intptr_t)get(proximo)], obterCarta);
				//puts("<< Incrementando para proximo jogador >>");
				get(proximo) = (generic)(intptr_t)( (((int)(intptr_t)get(proximo))+1)%((int)(intptr_t)get(emJogo)));
				//puts("<< Verificando maior carta da mesa >>");
				maior = (int)(intptr_t)call(&this, verMaior, c);
				//printf("A maior carta é %d\n\n", maior);
			}
			/* Verifica quem venceu */
			call((Object*)get(mesa), limpar);
			if(maior<0){// Empate
				puts("Empatou!");
				if(turno>1 && (int)(intptr_t)call((Object*)get(mesa), getPartida) !=0)
					break;
				continue;
			}
			else if(maior%2==0){// Time jogador marca
				call((Object*)get(mesa), add, 1);
			}
			else{// Time adversário marca
				call((Object*)get(mesa), add, 2);
			}
			puts("\n -------- \n");
			partida=(int)(intptr_t)call((Object*)get(mesa), getPartida);
			if(abs(partida) > 1)
				break;
			/* Quem ganha joga primeiro */
			get(proximo) = (generic)(intptr_t)maior;
		}
		/* Depois de jogarem todas as cartas, verifica qual time ganhou a rodada */
		call((Object*)get(mesa), finalizaRodada);
		/* Esvazia mão dos jogadores */
		for(i=0;i<(int)(intptr_t)get(emJogo);i++){
			call(&((Object*)get(jogadores))[i], esvaziarMao);
		}
		/* Separador */
		printf("\n\n --------[%d:%d]-------- \n\n", (int)(intptr_t)call((Object*)get(mesa), getTime1), (int)(intptr_t)call((Object*)get(mesa), getTime2) );
	}
	);