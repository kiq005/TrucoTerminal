#include "oo.h"

/* Definição das funções */
function(public, tar, 
	puts("tar");
	puts("tartar");
	);
function(private, bar, 
	puts("bar");
	);
function(public, foo, 
	puts("foo");
	);
function(public, sim,
	puts("sim");
	);
function(public, RA,
	puts("00112233");
	);
/* Definição das classes */
class(Pessoa, {&foo, &bar, &tar});
extends(Aluno, Pessoa, {&RA});
extends(Professor, Pessoa, {&sim});

int main(void){
	// Instaciações
	instanciate(fulano, Pessoa);
	instanciate(aluno, Aluno);
	instanciate(prof, Professor)
	// Teste de Chamada de funções
	call(fulano, foo);
	call(fulano, bar);
	call(fulano, tar);
	call(fulano, sim);
	call(fulano, RA);
	puts("---");
	call(aluno, foo);
	call(aluno, bar);
	call(aluno, tar);
	call(aluno, sim);
	call(aluno, RA);
	puts("---");
	call(prof, foo);
	call(prof, bar);
	call(prof, tar);
	call(prof, sim);
	call(prof, RA);
	puts("---");

	return 1;
}