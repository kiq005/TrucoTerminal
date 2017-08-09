#include "oo.h"
/************************
* TODO: 
* - Testar objetos que contenham argumentos de um tipo definido pelo usuário!
	Ex.: Aluno tem professor (Aluno->Professor), Pessoa tem amigo (Pessoa->Pessoa)
* - get(valor) = (generic)(intptr_t)v;// <-- Tentar simplificar para evitar warning
**************************/

/* Definição de atributos */
var(public, char[64], nome);
var(public, int, idade);
var(public, int, anoFormatura);
/* Definição das classes */
class(Pessoa, {&nome});
extends(Aluno, Pessoa, {&idade});
extends(Professor, Pessoa);
extends(Formado, Aluno, {&anoFormatura});
/* Definindo inicializadores */
constructor(Aluno, 
	arg(char*, name);
	arg(int, i);
	get(nome) = name;
	get(idade) = (generic)(intptr_t)i;
	);
/* Definição das funções */
function(Pessoa, public, getName,
	return "Fulano";
	);
function(Pessoa, public, setName, 
	arg(char*, name);
	get(nome) = name;
	);
function(Aluno, public, setIdade, 
	arg(int, i);
	get(idade) = (generic)(intptr_t)i;
	);
function(Aluno, public, getIdade,
	return get(idade);
	);
function(Aluno, public, getName, 
	return get(nome);
	);
function(Formado, public, setAnoFormatura, 
	arg(int, i);
	get(anoFormatura)= (generic)(intptr_t)i;
	);
function(Formado, public, getAnoFormatura, 
	return get(anoFormatura);
	);
function(Formado, public, getName, 
	return "Veterano";
	);

int main(void){
	// Instaciações
	puts(">> Criando instâncias");
	//puts(">>>> fulano");
	instanciate(Pessoa, fulano);
	//puts(">>>> aluno1");
	instanciate(Aluno, aluno1);
	//puts(">>>> aluno2");
	instanciate(Aluno, aluno2, "Zebra");
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
	call(fulano, setIdade, 32);
	printf("Nome: %s\n", (char*)call(fulano, getName));// a chamada getName retorna "Fulano"
	printf("Idade: %d\n", (int)(intptr_t)call(fulano, getIdade));
	call(fulano, setName, "Josevaldo");
	call(fulano, setIdade, 34);
	printf("Nome: %s\n", (char*)call(fulano, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(fulano, getIdade));

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
	printf("Nome: %s\n", (char*)call(aluno3, getName));// O nome do aluno foi setado no inicializador
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

	/* Teste de desalocação */
	puts(">> Desalocando aluno1");
	delete(aluno1);
	call(aluno1, setName, "Ana");
	call(aluno1, setIdade, 18);
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(aluno1, getIdade));
	
	return 1;
}