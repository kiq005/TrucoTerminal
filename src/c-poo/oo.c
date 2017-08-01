#include "oo.h"

/* Definição das funções */
function(public, getName,
	//printf("Type: %s\n", (char*)this.attributes[0]->_type);
	//printf("Nome: %s\n", (char*)this.attributes[0]->_value);
	return get(nome);
	);
function(public, setName, 
	char* name = va_arg(args, char*);
	set(nome, name);
	);
function(public, setIdade, 
	int idade = va_arg(args, int);
	set(idade, (generic)(intptr_t)idade);
	);
function(public, getIdade,
	return get(idade);
	);

/* Definição de atributos */
var(public, char[64], nome);
var(public, int, idade);
/* Definição das classes */
class(Pessoa, {&getName, &setName}, {&nome});
extends(Aluno, Pessoa, {&setIdade, &getIdade}, {&idade});
extends(Professor, Pessoa);

int main(void){
	// Instaciações
	puts(">> Criando instâncias");
	instanciate(fulano, Pessoa);
	instanciate(aluno1, Aluno);
	instanciate(aluno2, Aluno);
	instanciate(aluno3, Aluno);
	instanciate(prof, Professor);
	// Teste de Chamada de funções
	//puts(">> Chamando funções em fulano");
	//printf("Nome: %s\n", (char*)call(fulano, getName));
	//call(fulano, setName, "João");
	//call(fulano, setIdade, 32);
	//printf("Nome: %s\n", (char*)call(fulano, getName));
	//printf("Idade: %d\n", (int)call(fulano, getIdade));
	call(fulano, setName, "Josevaldo");
	call(fulano, setIdade, 34);
	printf("Nome: %s\n", (char*)call(fulano, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(fulano, getIdade));

	call(aluno1, setName, "Ana");
	call(aluno1, setIdade, 18);
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Idade: %d\n", (int)(intptr_t)call(aluno1, getIdade));
/*
	puts("---");
	puts(">> Definindo alunos");
	call(aluno1, setName, "Ana");
	call(aluno2, setName, "Bia");
	call(aluno3, setName, "Carol");
	call(aluno1, setIdade, 18);
	call(aluno2, setIdade, 19);
	call(aluno3, setIdade, 20);
	puts(">> Obtendo nomes dos alunos");
	
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Idade: %d\n", (int)call(aluno1, getIdade));
	printf("Nome: %s\n", (char*)call(aluno2, getName));
	printf("Idade: %d\n", (int)call(aluno2, getIdade));
	printf("Nome: %s\n", (char*)call(aluno3, getName));
	printf("Idade: %d\n", (int)call(aluno3, getIdade));
	printf("Nome: %s\n", (char*)call(fulano, getName));
	printf("Idade: %d\n", (int)call(fulano, getIdade));

	puts(">> Redefinindo nomes dos alunos");
	call(aluno1, setName, "Ana Lee");
	call(aluno3, setName, "Carol Chun");
	puts(">> Obtendo nomes dos alunos");
	printf("Nome: %s\n", (char*)call(aluno1, getName));
	printf("Nome: %s\n", (char*)call(aluno2, getName));
	printf("Nome: %s\n", (char*)call(aluno3, getName));
	printf("Nome: %s\n", (char*)call(fulano, getName));
*/

	return 1;
}