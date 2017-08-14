/*************
 * Atributos *
 *************/
var(public, Object, maior);
var(public, Object, vira);
var(public, int, time1);
var(public, int, time2);
var(public, int, rodada);
var(public, int, valor_rodada);

/**********
 * Classe *
 **********/
class(Mesa, {&maior, &vira, &time1, &time2, &rodada, &valor_rodada});

/**************
 * Construtor *
 **************/
constructor(Mesa, 
	instanciate(Carta, m, _CNONE, _NONAIPE);
	instanciate(Carta, v, _CNONE, _NONAIPE);
	get(vira) = v;
	get(maior) = m;
	get(time1) = (generic)(intptr_t)0;
	get(time2) = (generic)(intptr_t)0;
	get(rodada) = (generic)(intptr_t)0;
	get(valor_rodada) = (generic)(intptr_t)1;
	);

/***********
 * Funções *
 ***********/
/*
 * Mesa:imprimeMesa - 
 * Imprime as informações da mesa e do jogo.
 */
function(Mesa, public, imprimeMesa,
	char *v, *m, *r;
	//puts("<< 1 >>");
	if(((Object*)get(vira))->_type!=NULL && (int)(intptr_t)call(get(vira), getValor)!=_CNONE ){
		v = (char*)call(get(vira), Desenho);
	}
	else{
		v = "";
	}
	//printf("<< Type Maior: %s >>\n", ((Object*)get(maior))->_type->_name);
	if(((Object*)get(maior))->_type!=NULL && (int)(intptr_t)call(get(maior), getValor)!=_CNONE){
		m = (char*)call(get(maior), Desenho);
	}
	else{
		m = "";
	}
	//puts("<< 3 >>");
	if((int)(intptr_t)get(rodada)>0){
		r = "Time 1 vencendo.";
	}
	else if((int)(intptr_t)get(rodada)<0){
		r = "Time 2 vencendo.";
	}
	else{
		r = "Empadada.";
	}
	//puts("<< 4 >>");
	printf("Vira: %s\tMaior %s.\nValor da Rodada: %d [%d:%d]\nRodada %s\n", v, m, (int)(intptr_t)get(valor_rodada), (int)(intptr_t)get(time1), (int)(intptr_t)get(time2), r);
	);
/*
 * Mesa:vira - 
 * Recebe um Object* do tipo Carta, e o define como o vira
 */
function(Mesa, public, vira,
	arg(Object*, v);
	get(vira) = v;
	);
/*
 * Mesa:add - 
 * Recebe um int, e adiciona a pontuação para o time correspondente
 */
function(Mesa, public, add,
	arg(int, time);
	if(time==2){
		get(rodada)--;
		puts("Time 2 marcou!");
	}
	else if(time==1){
		get(rodada)++;
		puts("Time 1 marcou!");
	}
	);
/*
 * Mesa:limpar - 
 * Limpa a mesa, nulificando a maior carta
 */
function(Mesa, public, limpar,
	//puts(" << LIMPANDO MESA >>");
	call((Object*)get(maior), nulificar);//get(maior)=NULL;
	);
/*
 * Mesa:finalizaRodada - 
 * Finaliza rodada, nulificando maior carta e o vira, e entrega os pontos ao time
 */
function(Mesa, public, finalizaRodada,
	//puts(" << FINALIZANDO RODADA >>");
	call((Object*)get(vira), nulificar);//get(vira)=NULL;
	call((Object*)get(maior), nulificar);//get(maior)=NULL;
	if((int)(intptr_t)get(rodada)>0){
		get(time1)=(generic)(intptr_t)((int)(intptr_t)(get(time1))+(int)(intptr_t)get(valor_rodada));
	}
	else if((int)(intptr_t)get(rodada)<0){
		get(time2)=(generic)(intptr_t)((int)(intptr_t)(get(time2))+(int)(intptr_t)get(valor_rodada));
	}
	get(valor_rodada)=(generic)(intptr_t)1;
	get(rodada)=(generic)(intptr_t)0;
	);
/*
 * Mesa:getVira - 
 * Retorna generic Object* do tipo Carta com o vira
 */
function(Mesa, public, getVira,
	return get(vira);
	);
/*
 * Mesa:setMaior - 
 * Recebe Object* do tipo Carta e define como a maior carta da mesa
 */
function(Mesa, public, setMaior,
	arg(Object*, c);
	get(maior) = c;
	);
/*
 * Mesa:getMaior - 
 * Retorna generic Object* do tipo Carta com a maior carta da mesa
 */
function(Mesa, public, getMaior,
	return get(maior);
	);
/*
 * Mesa:getTime1 - 
 * Retorna generic int com a pontuação do time 1
 */
function(Mesa, public, getTime1,
	return get(time1);
	);
/*
 * Mesa:getTime2 - 
 * Retorna generic int com a pontuação do time 2
 */
function(Mesa, public, getTime2,
	return get(time2);
	);
/*
 * Mesa:getValor - 
 * Retorna generic int com o valor da rodada
 */
function(Mesa, public, getValor,
	return get(valor_rodada);
	);
/*
 * Mesa:getPartida - 
 * Retorna generic int com o número da rodada
 */
function(Mesa, public, getPartida,
	return get(rodada);
	);