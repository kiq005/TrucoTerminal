# Truco Terminal
Estamos simulando o paradigma de Orientação a Objetos em C, através de um jogo de truco para ser rodado via terminal.
## Executando
Utilize o `build.sh` para contruir o jogo. Um arquivo `Truco.sh` será gerado, utilize ele para testar o jogo no terminal!
(Atualmente, a versão construída é um modelo em Java, que servirá de base para a construção do modelo em C+OO)
## Programação OO via C
Para simular OO via C, primeiramente inclua a biblioteca _oo.h_, utilizando: `#include "oo.c"`, a biblioteca já inclui _stdlib.h_, _stdio.h_, e _string.h_. Atualmente contamos com as seguintes funcionalidades:

- **Definição de funções**

Para implementar, utilize: `function(visibilidade, nome, comandos...);`, por exemplo:
```C
function(public, foo,
	puts("bar");
	);
```
As funções não possuem um número determinado de argumentos, necessitando que o programador conheça a especificação da função. Um modo de definir argumentos é utilizar `tipo nome = va_arg(args, tipo)`, assim, a variável receberá o valor do primeiro argumento passado, pode-se repetir para quantas variáveis forem necessárias.

- ** Definição de atributos **

Assim como funções, os atributos de uma classe devem ser definidos primeiro. Atualmente, todos os atributos são tratados como `private`. Para implementar, utilize `var(visibilidade, tipo, nome)`, por exemplo:
```C
var(public, char[64], nome);
var(public, int, idade);
```
Os atributos só podem ser acessados por funções internas a classe. Para isso, utilize os comandos `get(nome_do_atributo)` e `set(nome_do_atributo, novo_valor)`. Por tratarem sobre um tipo genérico (void\*), seu compilador pode enviar mensagens de _warning_, isto deve ser trabalhado em próximas atualizações. 

- **Definição de classes**

Para definir classes, utilize: `class(nome, lista_de_métodos, lista_de_atributos);`, por exemplo:
```C
class(Pessoa, {&foo, &bar}, {&nome, &idade});
```
- **Definição de classes extendidas**

Para definir classes que herdam (filhas) de outras, use: `extends(nome, pai, lista_de_métodos, lista_de_atributos);`, por exemplo:
```C
extends(Aluno, Pessoa, {&nota}, {&ano});
```
- **Polimorfismo**

Para redefinir uma função herdada de uma classe pai, utilize: `override(Classe, nome_do_método, comandos...)`, por exemplo:
```C
override(Aluno, getName, 
	return get(nome);
```

- **Instânciação**

Para criar uma instância de uma classe, utilize `instanciate(classe, nome);`, não é preciso ter inicializado a variável antes.

- **Chamada de métodos**

Para realizar chamadas de métodos em objetos, utilize `call(objeto, função);`, por exemplo:
```C
instanciate(fulano, Aluno);
call(fulano, foo);
```
- ** Exemplo completo **

Um simples exemplo de utilização da biblioteca `oo.h` pode ser:
```C
/* Definição de funções*/
function(public, getName,
	return get(name);// Busca e retorna o atributo 'name' no objeto que implementa a função.
    );
function(public, setName,
	char* _name = va_arg(args, char*);// Faz com que a variável 'name' receba o primeiro argumento passado para função.
    set(name, _name);// Define o valor do atributo 'name' para '_name'(Tome cuidado com a nomenclatura!).
    );
function(public, getAge,
	return get(age);// Busca e retorna o atributo 'age' no objeto que implementa a função.
    );
function(public, setAge,
	int _age = va_arg(args, int);// Faz com que a variável '_age' receba o primeiro argumento passado para função.
    set(age, _age);// Define o valor do atributo 'age' para '_age'(Tome cuidado com a nomenclatura!).
    );
/* Definição de atributos */
var(public, char[64], name);
var(public, int, age);
/*Definição das classes*/
class(Person, {&getName, &setName}, {&name});// Argumentos: Nome_da_Classe, Lista_de_Funções, Lista_de_Atributos
extends(Studant, Person, {&getAge, &setAge}, {&name, &age});// A Classe Studant herda da Classe Person

/* Início da execução */
int main(void){
	/* Criando instâncias */
    instanciate(Studant, studant1);
    /* Chamando funções */
    call(studant1, setName, "Ana");// A classe Studant herda de Person a função setName
    call(studant1, setAge, 18);
    printf("Nome: %s\n", (char*)call(aluno, getName));
    printf("Idade: %s\n", (int)call(aluno, getIdade));
    
    return 1;
}
/* A compilação do código deve gerar warnings, porém você deve conseguir executar normalmente */
```

## Updates
03-08-17: Implementado polimorfismo de funções (_override_), apagado a função `__find_method_on_class__`, invertida a ordem de instanciação para `instanciate(tipo, nome)`, criada a macro `delete(obj)` para desalocar objetos instanciados, e agora as classes herdam também metodos e atributos de classes superiores além da classe pai. Foram adicionados várias saídas de debug (estão comentadas, nas proximas atualizações disponibilizaremos um modo debug), e algumas outras correções menores foram realizadas.

01-08-17: Classes filhas herdam diretamente atributos das classe pai. Foram reescritas algumas mentagens de erro.

28-07-17: Agora classes possuem atributos, e funções podem modificar e retornar tais atributos. Os atributos só podem ser modificados por funções internas a classe. No momento, os atributos devem ser endereçados nas classes pais e filhas, o mesmo não é necessário para as funções, precisando ser endereçadas somente na classe pai. Você deve tomar cuidado com as nomenclaturas ao utilizar a função `get(nome, valor)`, porém ela deve ser trabalhada para evitar problemas. A próxima atualização deve vir correções aos problemas citados. Utilize o arquivo `oo.c` para ter um exemplo de uso, retire comentários para poder ver alguns exemplos e limitações de tratamento de erros.

22-07-17: Adicionado primeira versão do arquivo ``oo.h``, possibilitando a implementação de classes, extensões(hierarquia de classes) e funções. As classes ainda não contém atributos! O escopo público e privado estão funcionando para controle de acesso a funções, ainda falta implementar o _protected_. Utilize o arquivo `oo.c` para ter um exemplo de uso das funcionalidades implementadas.

05-07-17: Modelagem em java, jogador humano contra IA aleatória(1x1).
## Coming soon
- Pedir truco, aceitar, correr, aumentar a aposta.
- Selecionar número de jogadores (1x1, 2x2, 3x3).
- IA melhorada.
