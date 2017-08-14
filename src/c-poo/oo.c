#include "oo.h"

/**************************
 * Definição de atributos *
 **************************/
var(public, char[64], nome);
var(public, int, idade);
var(public, int, anoFormatura);
var(public, Object, prof);

/*************************
 * Definição das classes *
 *************************/
class(Pessoa, {&nome});
extends(Aluno, Pessoa, {&prof, &idade});
extends(Professor, Pessoa, {});
extends(Formado, Aluno, {&anoFormatura});

/*****************************
 * Definindo inicializadores *
 *****************************/
constructor(Aluno, 
	arg(char*, name);
	arg(int, i);
	get(nome) = name;
	get(idade) = (generic)(intptr_t)i;
	);

/*************************
 * Definição das funções *
 *************************/
/*
 * Pessoa:getName - 
 * Retorna generic char* com o nome da Pessoa.
 */
function(Pessoa, public, getName,
	return get(nome);
	);
/*
 * Pessoa:setName - 
 * Recebe um char*, e define o nome da Pessoa.
 */
function(Pessoa, public, setName, 
	arg(char*, name);
	get(nome) = name;
	);
/*
 * Pessoa:getUndefVar - 
 * Tenta obter uma variável não definida, gerando um erro.
 */
function(Pessoa, public, getUndefVar,
	return get(undef);
	);
/*
 * Aluno:setIdade - 
 * Recebe um int, e define a idade do Aluno.
 */
function(Aluno, public, setIdade, 
	arg(int, i);
	get(idade) = (generic)(intptr_t)i;
	);
/*
 * Aluno:getIdade - 
 * Retorna um generic int com a idade do Aluno.
 */
function(Aluno, public, getIdade,
	return get(idade);
	);
/*
 * Aluno:getName - 
 * Retorna um generic char* com o nome do Aluno.
 */
function(Aluno, public, getName, 
	return get(nome);
	);
/*
 * Aluno:setProf - 
 * Recebe um Object*, e define o Professor do Aluno.
 */
function(Aluno, public, setProf,
	arg(Object*, p);
	get(prof) = p;
	);
/*
 * Aluno:getProf - 
 * Retorna um generic Object* com o Professor do Aluno.
 */
function(Aluno, public, getProf, 
	return get(prof);
	);
/*
 * Formado:setAnoFormatura - 
 * Recebe um int, e define o ano de formatura do aluno Formado.
 */
function(Formado, public, setAnoFormatura, 
	arg(int, i);
	get(anoFormatura)= (generic)(intptr_t)i;
	);
/*
 * Formado:getAnoFormatura - 
 * Retorna um generic int com o ano de formatura do aluno Formado.
 */
function(Formado, public, getAnoFormatura, 
	return get(anoFormatura);
	);
/*
 * Formado:getName - 
 * Retorna um generic char* com o "Veterano".
 */
function(Formado, public, getName, // 
	return "Veterano";
	);
/**********************
 * Início do programa *
 **********************/
int main(void){
	// Instaciações
	puts(">> Criando instâncias");
	//puts(">>>> fulano");
	instanciate(Pessoa, fulano);
	//puts(">>>> aluno1");
	instanciate(Aluno, aluno1);
	//puts(">>>> aluno2");
	instanciate(Aluno, aluno2, "Zebra", 40);
	//puts(">>>> aluno3");
	instanciate(Aluno, aluno3);
	//puts(">>>> prof");
	instanciate(Professor, prof);
	//puts(">>>> form");
	instanciate(Formado, form);
	// Teste de Chamada de funções
	puts(">> Chamando funções em fulano");
	printf("Nome: %s\n", (char*)call(fulano, getName));
	call(fulano, setName, "João");
	printf("Nome: %s\n", (char*)call(fulano, getName));// a chamada getName retorna "Fulano"
	call(fulano, setIdade, 32);
	printf("Idade: %d\n", (int)(intptr_t)call(fulano, getIdade));
	printf("Variável Indefinida: %s\n", (char*)call(fulano, getUndefVar));
	call(fulano, setName, "Josevaldo");
	printf("Nome: %s\n", (char*)call(fulano, getName));

	/* Testando herança direta */
	puts(">> Chamando funções em aluno1");
	call(aluno1, setName, "Ana");
	call(aluno1, setIdade, 18);
	printf("Nome: %s\n", (char*)call(aluno1, getName));// A chamada getName vai para o método sobrecarregado
	printf("Idade: %d\n", (int)(intptr_t)call(aluno1, getIdade));
	/* Testando herança em profundidade */
	puts(">> Chamando funções em form");
	call(form, setName, "Carlos");
	call(form, setIdade, 26);
	printf("Nome: %s\n", (char*)call(form, getName));// A chamada getName vai para o método sobrecarregado em Aluno
	printf("Idade: %d\n", (int)(intptr_t)call(form, getIdade));
	
	/* Testando várias instancias */
	puts(">> Testando inicializador");
	printf("Nome: %s\n", (char*)call(aluno2, getName));// O nome do aluno foi setado no inicializador
	printf("Idade: %d\n", (int)(intptr_t)call(aluno2, getIdade));
	printf("Nome: %s\n", (char*)call(aluno3, getName));// O nome do aluno foi setado no inicializador
	printf("Idade: %d\n", (int)(intptr_t)call(aluno3, getIdade));
	puts(">> Definindo alunos");
	call(aluno1, setName, "Ana");
	call(aluno2, setName, "Bia");
	call(aluno3, setName, "Carol");
	call(aluno1, setIdade, 18);
	call(aluno2, setIdade, 19);
	call(aluno3, setIdade, 20);
	puts(">> Obtendo nomes dos alunos");
	
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(aluno1, getIdade));
	printf("Nome: %s\n", (char*)call(aluno2, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(aluno2, getIdade));
	printf("Nome: %s\n", (char*)call(aluno3, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(aluno3, getIdade));
	printf("Nome: %s\n", (char*)call(fulano, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(fulano, getIdade));

	puts(">> Redefinindo nomes dos alunos");
	call(aluno1, setName, "Ana Lee");
	call(aluno3, setName, "Carol Chun");
	puts(">> Obtendo nomes dos alunos");
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Nome: %s\n", (char*)call(aluno2, getName));
	printf("Nome: %s\n", (char*)call(aluno3, getName));
	printf("Nome: %s\n", (char*)call(fulano, getName));

	puts(">> Testes com TADs");
	call(prof, setName, "Adolfo");
	call(aluno1, setProf, prof);
	printf("%s é aluno de %s.\n", (char*)call(aluno1, getName), (char*)call((Object*)(call(aluno1, getProf)), getName));

	/* Teste de desalocação, pode gerar erro ao tentar acessar variável desalocada*/
	puts(">> Desalocando aluno1");
	delete(aluno1);
	call(aluno1, setName, "Ana");
	call(aluno1, setIdade, 18);
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(aluno1, getIdade));
	
	return 0;
}