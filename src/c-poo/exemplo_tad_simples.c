#include "oo.h"

/* Criamos as variáveis que serão usadas no programa */
var(public, char[64], nome);
var(public, Object, prof);
/* Classe Pessoa, que possui o atributo nome, e as funções getName e setName */
class(Pessoa, {&nome});
/** 
 * getName:
 *  Retorna generic char* com o nome da pessoa.
 */
function(Pessoa, public, getName, 
	return get(nome);
    );
/** 
 * setName:
 *  Recebe como parâmetro um char* name, e define o nome da pessoa como name.
 */
function(Pessoa, public, setName, 
	arg(char*, name);
    get(nome) = name;
    );
/* Classe Aluno, que herda de Pessoa, possui o atributo prof, e as funções getProf e setProf */
extends(Aluno, Pessoa, {&prof});
/** 
 * getProf:
 *  Retorna generic Object com o professor do aluno.
 */
function(Aluno, public, getProf,
	return get(prof);
    );
/** 
 * setProf:
 *  Recebe como parâmetro um Object p, e define o professor do aluno como p.
 */
function(Aluno, public, setProf,
	arg(Object*, p);
    get(prof) = p;
	);
/* Classe Professor, que herda de Pessoa, e não possui atributos próprios */
extends(Professor, Pessoa, {});
/** 
 * getName:
 *  Retorna generic char* com o nome do Professor. Deve utilizar free depois do uso.
 */
function(Professor, public, getName, // Override!
    char *str = (char*) malloc(sizeof("Prof.") + sizeof((char*)get(getName)));
    strcpy(str, "Prof. ");
    strcat(str, (char*)get(nome));
    return str;
    );

/* Início do programa */
int main(void){
    char *nome_prof;
    /* Instanciação de classes */
	instanciate(Aluno, aluno1);
    instanciate(Professor, prof1);
    /* Chamamos setName no objeto aluno1 e prof1, que são do tipo Aluno e Professor, respectivamente.
    Como não há sobrecarga, as chamadas correspondem a chamada do método na classe Pessoa. */
    call(aluno1, setName, "Pedro");
    call(prof1, setName, "Carlos");
    /* Chamamos setProf no objeto aluno1. Esta função é exclusiva desta classe, uma vez que nenhuma 
    classe herda de aluno, ou implementa uma função de mesmo nome. */
    call(aluno1, setProf, prof1);
    /* Ao chamar call(aluno1, getName), obteremos o nome do aluno via a função implementada em Pessoa.
    Na chamada call((Object*)(call(aluno1, getProf)), getName), primeiro obtemos o professor do aluno, 
    e então chamamos no objeto obtido a função getName, que como foi reescrita na classe filha, deve 
    retornar 'Prof.'. As chamadas 'call' retornam um tipo 'generic', que deve ser convertido para char* */
    nome_prof = (char*)call((Object*)(call(aluno1, getProf)), getName);
    printf("%s é aluno do %s.\n", (char*)call(aluno1, getName), nome_prof);
    free(nome_prof);

	return 0;
}