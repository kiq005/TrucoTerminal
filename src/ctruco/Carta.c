/**************
 * Constantes *
 **************/
#define _C4 0
#define _C5 1
#define _C6 2
#define _C7 3
#define _CQ 4
#define _CJ 5
#define _CK 6
#define _CA 7
#define _C2 8
#define _C3 9
#define _CNONE -1

#define _OURO 0
#define _ESPADAS 1
#define _COPAS 2
#define _PAUS 3
#define _NONAIPE -1

#define _PERDE -1
#define _EMPATA 0
#define _GANHA 1

/*************
 * Atributos *
 *************/
var(public, int, valor);
var(public, int, naipe);

/**********
 * Classe *
 **********/
class(Carta, {&valor, &naipe});

/*******************************************************
 * Construtor - 									   *
 * Recebe dois int, contento o valor e naipe da carta. * 
 *******************************************************/
constructor(Carta, 
	arg(int, v);
	arg(int, n);
	get(valor) = (generic)(intptr_t)v;
	get(naipe) = (generic)(intptr_t)n;
	//printf("Carta criada: %d:%d - %s\n", v, n, (char*)call(&this, Desenho));
	);

/***********
 * Funções *
 ***********/
/*
 * Carta:Desenho - 
 * Retorna um generic char* com o Desenho da carta
 */
function(Carta, public, Desenho, 
	char *carta = (char*)malloc(4);
	switch((int)(intptr_t)get(valor)){
		case _C4:
			carta[0] = '4';
			break;
		case _C5:
			carta[0] = '5';
			break;
		case _C6:
			carta[0] = '6';
			break;
		case _C7:
			carta[0] = '7';
			break;
		case _CQ:
			carta[0] = 'Q';
			break;
		case _CJ:
			carta[0] = 'J';
			break;
		case _CK:
			carta[0] = 'K';
			break;
		case _CA:
			carta[0] = 'A';
			break;
		case _C2:
			carta[0] = '2';
			break;
		case _C3:
			carta[0] = '3';
			break;
		case _CNONE:
			carta[0] = ' ';
			break;
		default:
			fprintf(stderr, "Erro: Valor de carta não identificado.\n");
	}
	switch((int)(intptr_t)get(naipe)){
		case _OURO:
			carta[1] = 'o';
			break;
		case _COPAS:
			carta[1] = 'c';
			break;
		case _ESPADAS:
			carta[1] = 'e';
			break;
		case _PAUS:
			carta[1] = 'p';
			break;
		case _NONAIPE:
			carta[1] = ' ';
			break;
		default:
			fprintf(stderr, "Erro: Naipe não identificado.\n");
	}
	carta[2] = '\0';
	carta[3] = '\0';
	return carta;
	);
/*
 * Carta:Desenho - 
 * Recebe dois Objetos, sendo o vira e a carta, e verifica se ela é manilha,
 * retornando um generic int 1 caso verdadeiro, 0 caso falso.
 */
function(Carta, public, Manilha, 
	arg(Object*, c);
	arg(Object*, vira);
	int cVal, vVal;
	//printf("<< Deseinho carta: %s>>\n", (char*)call(c, Desenho));
	//printf("<< Deseinho vira: %s>>\n", (char*)call(vira, Desenho));
	cVal = (int)(intptr_t)call(c, getValor);
	vVal = (int)(intptr_t)call(vira, getValor);
	return (generic)(intptr_t)((cVal == vVal+1) || (cVal == _C4 && vVal == _C3));
	);
/*
 * Carta:Ganha - 
 * Recebe dois Objetos, sendo o vira e a outra carta, e verifica se esta carta
 * a vence, retornando um generic int com _GANHA, _EMPATA ou _PERDE.
 */
function(Carta, public, Ganha,
	arg(Object*, outra);
	arg(Object*, vira);
	//puts("<< Disputando >>");
	if(outra==NULL || (int)(intptr_t)call(outra, getValor)==_CNONE || (int)(intptr_t)call(outra, getValor)==_NONAIPE)
		return (generic)(intptr_t)_GANHA;
	//printf("<< Deseinho carta: %s>>\n", (char*)call(&this, Desenho));
	//printf("<< Deseinho outra: %s>>\n", (char*)call(outra, Desenho));
	//printf("<< Deseinho vira: %s>>\n", (char*)call(vira, Desenho));
	//puts("<< Verificando >>");
	if((int)(intptr_t)call(&this, Manilha, &this, vira)){
		//puts("<< Vendo se perde >>");
		if((int)(intptr_t)call(&this, Manilha, outra, vira) && ((int)(intptr_t)call(&this, getNaipe) < (int)(intptr_t)call(outra, getNaipe))){
			//puts("<< PERDEU >>");
			return (generic)(intptr_t)_PERDE;
		}
		//puts("<< GANHOU >>");
		return (generic)(intptr_t)_GANHA;
	}
	else{
		//puts("<< Não é maniha >>");
		//printf("<< Deseinho outra: %s>>\n", (char*)call(outra, Desenho));
		if((int)(intptr_t)call(&this, Manilha, outra, vira) || ((int)(intptr_t)call(&this, getValor) < (int)(intptr_t)call(outra, getValor)) ){
			//puts("<< PERDEU 2 >>");
			return (generic)(intptr_t)_PERDE;
		}
		//puts("<< GANHOU 2 >>");
		return (generic)(intptr_t)_GANHA;
	}
	//puts("<< Empatou >>");
	return (generic)(intptr_t)_EMPATA;
	);
/*
 * Carta:getValor - 
 * Retorna um generic int com o valor da carta
 */
function(Carta, public, getValor,
	return get(valor);
	);
/*
 * Carta:setValor - 
 * Recebe um int, e define o valor da carta.
 */
function(Carta, public, setValor,
	arg(int, v);
	get(valor) = (generic)(intptr_t)v;
	);
/*
 * Carta:getNaipe - 
 * Retorna um generic int com o Naipe da carta
 */
function(Carta, public, getNaipe,
	return get(naipe);
	);
/*
 * Carta:setNaipe - 
 * Recebe um int, e define o valor da carta.
 */
function(Carta, public, setNaipe,
	arg(int, n);
	get(naipe) = (generic)(intptr_t)n;
	);
/*
 * Carta:Desenho - 
 * Define o valor e naipe da carta como nulos
 */
function(Carta, public, nulificar,
	get(naipe) = (generic)(intptr_t)_NONAIPE;
	get(valor) = (generic)(intptr_t)_CNONE;
	);