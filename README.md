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
- **Definição de classes**

Para definir classes, utilize: `class(nome, lista_de_métodos);`, por exemplo:
```C
class(Pessoa, {&foo, &bar});
```
- **Definição de classes extendidas**

Para definir classes que herdam (filhas) de outras, use: `extends(nome, pai, lista_de_métodos);`, por exemplo:
```C
extends(Aluno, Pessoa, {&Nota});
```
- **Instânciação**

Para criar uma instância de uma classe, utilize `instanciate(nome, classe);`, não é preciso ter inicializado a variável antes.
- **Chamada de métodos**

Para realizar chamadas de métodos em objetos, utilize `call(objeto, função);`, por exemplo:
```C
instanciate(fulano, Aluno);
call(fulano, foo);
```

## Updates
22-07-17: Adicionado primeira versão do arquivo ``oo.h``, possibilitando a implementação de classes, extensões(hierarquia de classes) e funções. As classes ainda não contém atributos! O escopo público e privado estão funcionando para controle de acesso a funções, ainda falta implementar o _protected_. Utilize o arquivo `oo.c` para ter um exemplo de uso das funcionalidades implementadas.

05-07-17: Modelagem em java, jogador humano contra IA aleatória(1x1).
## Coming soon
- Pedir truco, aceitar, correr, aumentar a aposta.
- Selecionar número de jogadores (1x1, 2x2, 3x3).
- IA melhorada.
