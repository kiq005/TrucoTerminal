
/* Constantes sobre definição */

/* Atributos */
var(public, Object, maior);
var(public, Object, vira);
var(public, int, time1);
var(public, int, time2);
var(public, int, rodada);
var(public, int, valor_rodada);
/* Classe */
class(Mesa, {&maior, &vira, &time1, &time2, &rodada, &valor_rodada});
/* Construtor */
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
/* Métodos */
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
		r = "Empadado.";
	}
	//puts("<< 4 >>");
	printf("Vira: %s\tMaior %s.\nValor da Rodada: %d [%d:%d]\n", v, m, (int)(intptr_t)get(valor_rodada), (int)(intptr_t)get(time1), (int)(intptr_t)get(time2));
	);

function(Mesa, public, vira,
	arg(Object*, v);
	get(vira) = v;
	);
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
function(Mesa, public, limpar,
	puts(" << LIMPANDO MESA >>");
	call((Object*)get(maior), nulificar);//get(maior)=NULL;
	);
function(Mesa, public, finalizaRodada,
	puts(" << FINALIZANDO RODADA >>");
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
function(Mesa, public, getVira,
	return get(vira);
	);
function(Mesa, public, setMaior,
	arg(Object*, c);
	get(maior) = c;
	);
function(Mesa, public, getMaior,
	return get(maior);
	);
function(Mesa, public, getTime1,
	return get(time1);
	);
function(Mesa, public, getTime2,
	return get(time2);
	);
function(Mesa, public, getValor,
	return get(valor_rodada);
	);
function(Mesa, public, getPartida,
	return get(rodada);
	);