#include "oo.h"

var(public, char[64], nome);
var(public, Object, prof);

class(Pessoa, {&nome});
extends(Aluno, Pessoa, {&prof});
extends(Professor, Pessoa, {});

function(Pessoa, public, getName, 
	return get(nome);
    );
function(Pessoa, public, setName, 
	arg(char*, name);
    get(nome) = name;
    );
function(Aluno, public, getProf,
	return get(prof);
    );
function(Aluno, public, setProf,
	arg(Object*, p);
    get(prof) = p;
	);

int main(void){
	instanciate(Aluno, aluno1);
    instanciate(Professor, prof1);
    
    call(aluno1, setName, "Pedro");
    call(prof1, setName, "Carlos");
    call(aluno1, setProf, prof1);
    
    printf("%s é aluno de %s.\n", (char*)call(aluno1, getName), (char*)call((Object*)(call(aluno1, getProf)), getName));
    
	return 0;
}