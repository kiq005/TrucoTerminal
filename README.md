# Truco Terminal
Estamos simulando o paradigma de Orientação a Objetos em C, através de um jogo de truco para ser rodado via terminal.
## Executando
Utilize o `build.sh` para contruir o jogo. Um arquivo `Truco.sh` será gerado, utilize ele para testar o jogo no terminal!
(Atualmente, a versão construída é um modelo em Java, que servirá de base para a construção do modelo em C+OO)
## Programação OO via C
Para simular OO via C, primeiramente inclua a biblioteca _oo.h_, utilizando: `#include "oo.c"`, a biblioteca já inclui _stdlib.h_, _stdio.h_, e _string.h_. Atualmente contamos com as seguintes funcionalidades:

- **Definição de funções**

Para implementar funções em classes, utilize: `function(classe, visibilidade, nome, comandos...);`, por exemplo:
```C
function(Pessoa, public, getName,
	return "Fulano";
	);
```
As funções não possuem um número determinado de argumentos, necessitando que o programador conheça a especificação da função. Um modo de definir argumentos é utilizar `arg(tipo, nome)`, assim, a variável receberá o valor do primeiro argumento passado, pode-se repetir para quantas variáveis forem necessárias.
Uma função pode ser sobrecarregada, para isso, basta defini-la em diferentes classes, por exemplo:
```C
function(Aluno, public, getName,
	return "Aluno";
	);
function(Professor, public, getName,
	return "Prof.";
	);
```
Ambas as funções serão acessadas pelo nome **getName**, porém cada uma será chamada em objetos de suas respectivas classes.

- ** Definição de atributos **

Assim como funções, os atributos de uma classe devem ser definidos primeiro. Atualmente, todos os atributos são tratados como `private`. Para implementar, utilize `var(visibilidade, tipo, nome)`, por exemplo:
```C
var(public, char[64], nome);
var(public, int, idade);
```
Os atributos só podem ser acessados por funções internas a classe. Para isso, utilize o comando `get(nome_do_atributo)`. Por tratarem sobre um tipo genérico (void\*), seu compilador pode enviar mensagens de _warning_, isto deve ser trabalhado em próximas atualizações. 

- **Definição de classes**

Para definir classes, utilize: `class(nome, lista_de_atributos);`, por exemplo:
```C
class(Pessoa, {&nome, &idade});
```
- **Definição de classes extendidas**

Para definir classes que herdam (filhas) de outras, use: `extends(nome, pai, lista_de_atributos);`, por exemplo:
```C
extends(Aluno, Pessoa, {&nota}, {&ano});
```

- **Inicialização**

A definição do construtor de uma classe é parecido com o de uma função, basta utilizar `constructor(Classe, comandos...)`, por exemplo:
```C
constructor(Aluno, 
	arg(char*, name);
    arg(int, i);
    get(nome) = name;
    get(idade) = (generic)(intptr_t)i;
```

- **Instânciação**

Para criar uma instância de uma classe, utilize `instanciate(classe, nome);`, não é preciso ter inicializado a variável antes. Caso a instância receba parâmetros de inicialização, você pode passa-los normalmente pela mesma macro, utilize `instanciate(classe, nome, arg1, arg2, ...)`.

- **Chamada de métodos**

Para realizar chamadas de métodos em objetos, utilize `call(objeto, função);`, por exemplo:
```C
instanciate(Aluno, aluno, "Ana");
printf("Nome: %s\n", (char*)call(aluno, getName));
call(aluno, setName, "Bia");
printf("Nome: %s\n", (char*)call(aluno, getName));
```

- ** Exemplo completo **

Um simples exemplo de utilização da biblioteca `oo.h` pode ser:
```C
#include "oo.h"
/* Definição de atributos */
var(public, char[64], nome);
var(public, int, idade);
var(public, int, anoFormatura);
/* Definição das classes */
class(Pessoa, {&nome});
extends(Aluno, Pessoa, {&idade});// A Classe Aluno herda da Classe Pessoa
extends(Professor, Pessoa);// A Classe Professor herda da Classe Pessoa
extends(Formado, Aluno, {&anoFormatura});// A Classe Formado herda da Classe Aluno
/* Definição de inicializadores */
constructor(Aluno,
    arg(char*, name);
    arg(int, i);
    get(nome) = name;
    get(idade) = (generic)(intptr_t)i;
    );
/* Definição de funções */
function(Pessoa, public, getNome,
    return "Fulano";
    );
function(Pessoa, public, setNome, 
    arg(char*, name);// A função recebe um argumento do tipo char* e define a variável local name
    get(nome) = name;// Busca no objeto a variável nome e define o valor dela para o valor do argumento name
    );
function(Aluno, public, setIdade, 
    arg(int, i);
    get(idade) = (generic)(intptr_t)i;
    );
function(Aluno, public, getIdade,
    return get(idade);// Busca e retorna a variável idade no objeto
    );
function(Aluno, public, getNome, // Sobrecarrega o método setNome da classe super(Pessoa)
    return get(nome);
    );
function(Formado, public, setAnoFormatura, 
    arg(int, i);
    get(anoFormatura)= (generic)(intptr_t)i;
    );
function(Formado, public, getAnoFormatura, 
    return get(anoFormatura);
    );
function(Formado, public, getNome, // Sobrecarrega o método setNome da classe super(Aluno)
    return "Veterano";
    );

/* Início da execução */
int main(void){
    /* Criando instâncias */
    instanciate(Aluno, aluno, "Ana", 17);
    instanciate(Professor, professor);
    instanciate(Formado, formado);
    /* Chamando funções */
    printf("Nome: %s\n", (char*)call(aluno, getNome));
    printf("Idade: %d\n", (int)(intptr_t)call(aluno, getIdade));
    call(aluno, setNome, "Bia");// A classe Studant herda de Person a função setName
    call(aluno, setIdade, 18);
    printf("Nome: %s\n", (char*)call(aluno, getNome));
    printf("Idade: %d\n", (int)(intptr_t)call(aluno, getIdade));
    printf("Nome: %s\n", (char*)call(professor, getNome));// Como não houve sobrecarga, deve chamar a função getName da classe Pessoa
    return 1;
}
```

## Updates
09-08-17: Diversas mudanças significativas foram realizadas nesta versão. Primeiramente, agora todas as classes herdam de `__OBJECT__`, ao invés de manter uma referência `NULL` para a super, isto foi feito para permitir um uso correto de uma função de inicialização. Além disso, antes não era possível sobrecarregar uma função em diferentes classes, por exemplo, ao definir a função `getName()` na classe Pessoa, ela só poderia ser sobrecarregada na classe Aluno ou Professor, que herdam da classe pessoa, mas não nas duas; este erro foi corrigido. Ainda sobre **override**, a macro tomou lugar da **function**, assim, não é mais necessário definir funções, marca-las nas classes, e depois realizar sobrecargas marcadas; agora basta declarar as funções, indicando á qual classe ela pertence. Também foram criadas as macros **EVALUATOR** e **PASTER**, com base em https://stackoverflow.com/questions/1489932/how-to-concatenate-twice-with-the-c-preprocessor-and-expand-a-macro-as-in-arg para permitir concatenação multipla no preprocessador. Outra macro criada é a **arg** que simplesmente simplifica a tomada de argumentos em uma função. Note que a macro **override** foi removida, e além dela, a macro **set**, pois ela não permitia trabalho com _array_ ou matrizes, assim, utilize `get(nome) = valor` ao invés. Para definir a função de inicialização de um objeto, basta utilizar a nova macro **constructor**, com o nome da classe e os comandos. Os argumentos do inicializador são passados na macro **instanciate**. Outras pequenas correções foram feitas para que a compilação, utilizando o compilador **gcc** com as _flag _ **-Wall** e **-Wextra** não gere mensagens de _warning_, como a criação das macros **DEF_CLASS**, **CLASS1**, **CLASS2**, **DEF_EXTENDS**, **EXTENDS2**, **EXTENDS3**, (com base em https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments), para permitir que as macros **class** e **extends** tenham sobrecarga para chamadas com 1 e 2, 2 e 3 argumentos, respectivamente.

03-08-17: Implementado polimorfismo de funções (_override_), apagado a função `__find_method_on_class__`, invertida a ordem de instanciação para `instanciate(tipo, nome)`, criada a macro `delete(obj)` para desalocar objetos instanciados, e agora as classes herdam também metodos e atributos de classes superiores além da classe pai. Foram adicionados várias saídas de debug (estão comentadas, nas proximas atualizações disponibilizaremos um modo debug), e algumas outras correções menores foram realizadas.

01-08-17: Classes filhas herdam diretamente atributos das classe pai. Foram reescritas algumas mentagens de erro.

28-07-17: Agora classes possuem atributos, e funções podem modificar e retornar tais atributos. Os atributos só podem ser modificados por funções internas a classe. No momento, os atributos devem ser endereçados nas classes pais e filhas, o mesmo não é necessário para as funções, precisando ser endereçadas somente na classe pai. Você deve tomar cuidado com as nomenclaturas ao utilizar a função `get(nome, valor)`, porém ela deve ser trabalhada para evitar problemas. A próxima atualização deve vir correções aos problemas citados. Utilize o arquivo `oo.c` para ter um exemplo de uso, retire comentários para poder ver alguns exemplos e limitações de tratamento de erros.

22-07-17: Adicionado primeira versão do arquivo ``oo.h``, possibilitando a implementação de classes, extensões(hierarquia de classes) e funções. As classes ainda não contém atributos! O escopo público e privado estão funcionando para controle de acesso a funções, ainda falta implementar o _protected_. Utilize o arquivo `oo.c` para ter um exemplo de uso das funcionalidades implementadas.

05-07-17: Modelagem em java, jogador humano contra IA aleatória(1x1).
## Coming soon
- Pedir truco, aceitar, correr, aumentar a aposta.
- Selecionar número de jogadores (1x1, 2x2, 3x3).
- IA melhorada.
