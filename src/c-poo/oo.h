
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
/**************
 * Definições *
 **************/
#define __MAX_MET__ 256 	// Número máximo de métodos de uma classe, incluindo métodos herdados
#define __MAX_STR_LEN__ 64	// Tamanho máximo do nome de uma variável, classe, ou método
#define generic void*		// Tipo generico definido sobre void*

/***********************
 * Definições de tipos *
 ***********************/
typedef enum{private, public, protected} scope; // Escopo de funções e variáveis
typedef struct Class Class;			// Definição do tipo Classe
typedef struct Attribute Attribute; // Definição do tipo Atributo
typedef struct Method Method;		// Definição do tipo Método/Função
typedef struct Object Object;		// Definição do tipo Objeto

/************************
 * Cabeçalho de funções *
 ************************/
static int __get_attribute_index__(Object this, int _callLine_, char* _callFile_,char* att_name);
static generic __realize_call__(Object *_obj, int _callLine_, char* _callFile_, char* func, ...);
static generic __find_method_on_object__(Object _obj_, int _callLine_,  char* _callFile_,char* func, va_list args);

/**************************
 * Variáveis de uso local *
 **************************/
static int __i__, __j__;
static Object _scope_;

/***********************
 * Definição de Macros *
 ***********************/
/* Macro: class - 
 * Utilizada para definir classes
 */
#define class(name, ...) Class name = {&__OBJECT__, #name, {}, ##__VA_ARGS__}

/* Macro: extends - 
 * Utilizada para definir classes que herdam de outra
 */
#define extends(name, super, ...) Class name = {&super, #name, {}, ##__VA_ARGS__}

/* Macro: instanciate - 
 * Utilizada para definir instâncias de classes, ou seja, objetos. Eles devem ser
 * desalocados com a macro delete depois do uso
 */
#define instanciate(_type_, name, ...) \
	Object* name = (Object*)malloc(sizeof(Object));\
	name->_type = &_type_;\
	for(__i__=0;__i__<__MAX_MET__; __i__++){\
		name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
		if(_type_._attributes[__i__]==NULL){\
			if(_type_._super==NULL) continue;\
			break;\
		}\
		name->attributes[__i__]->_visibility = _type_._attributes[__i__]->_visibility;\
		strncpy(name->attributes[__i__]->_type, _type_._attributes[__i__]->_type, __MAX_STR_LEN__);\
		strncpy(name->attributes[__i__]->_name, _type_._attributes[__i__]->_name, __MAX_STR_LEN__);\
		name->attributes[__i__]->_value = NULL;\
	}\
	/*Herdando atributos de classes superiores*/\
	if(name->_type!=NULL){\
		Class _super_ = *name->_type;\
		while(1){\
			/*printf("DEBUG: vendo atributos de %s.\n", _super_._name);*/\
			for(__j__=0;__i__<__MAX_MET__ && _super_._attributes[__j__]!=NULL; __i__++, __j__++){\
				name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
				if(_super_._attributes[__j__]==NULL) continue; \
				name->attributes[__i__]->_visibility = _super_._attributes[__j__]->_visibility;\
				strncpy(name->attributes[__i__]->_type, _super_._attributes[__j__]->_type, __MAX_STR_LEN__);\
				strncpy(name->attributes[__i__]->_name, _super_._attributes[__j__]->_name, __MAX_STR_LEN__);\
				name->attributes[__i__]->_value = NULL;\
				/*printf("DEBUG: Adicionado %s á %s.\n", name->attributes[__i__]->_name, #name);*/\
			}\
			if(_super_._super==NULL) break;\
			_super_ = *_super_._super;\
		}\
	}\
	/*Finaliza instanciação*/\
	for(;__i__<__MAX_MET__;__i__++){\
		name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
	}\
	/*Chama o método de inicialização*/\
	__realize_call__(name, __LINE__, __FILE__, "__init__", ##__VA_ARGS__ );

/* Macro: delete - 
 * Utilizada para liberar espaço em memória alocado por objetos
 */
#define delete(_obj_)\
	for(__i__=0; __i__<__MAX_MET__; __i__++){\
		free(_obj_->attributes[__i__]);\
	}\
	free(_obj_)

/* Macro: var - 
 * Utilizada para definir variáveis que serão utilizados como atributos em Classes.
 * OBS: Atualmente, apesar de manter o tipo e visibilidade do atributo, ambos não são
 * utilizados.
 */
#define var(visibility, type, name) \
	static Attribute name = {visibility, #type, #name, NULL};

/* Macro: CONCAT - 
 * Concatena x e y na forma x_y
 */
#define CONCAT(x, y) x ## _ ## y

/* Macro: EVALUATOR - 
 * Permite multipla concatenação
 */
#define EVALUATOR(x, y) CONCAT(x, y)

/* Macro: function - 
 * Define funções dentro de classes.
 */
#define function(_class_, visibility, _name_, ...) \
	generic EVALUATOR(_, EVALUATOR(_class_,EVALUATOR(_name_, __LINE__))) (Object this, va_list args){__VA_ARGS__;this=this;va_end(args);return NULL;};\
	Method EVALUATOR(_o_, EVALUATOR(_class_,EVALUATOR(_name_, __LINE__))) = {visibility, #_name_, &EVALUATOR(_, EVALUATOR(_class_,EVALUATOR(_name_, __LINE__)))};\
	/*GNU C*/\
	__attribute__((constructor)) void EVALUATOR(_init_, EVALUATOR(_class_, EVALUATOR(_name_, __LINE__))) (){\
		for(__i__=0; __i__<__MAX_MET__; __i__++){ \
			if(_class_.methods[__i__]==NULL){ \
				_class_.methods[__i__]=&EVALUATOR(_o_, EVALUATOR(_class_,EVALUATOR(_name_, __LINE__))); \
				break; \
			} \
		} \
	};

/* Macro: constructor - 
 * Define o construtor de uma classe
 */
#define constructor(_class_, ...) \
	function(_class_, protected, __init__, __VA_ARGS__);

/* Macro: arg - 
 * Obtém argumentos passados para funções definidas pela macro function
 */
#define arg(type, name) \
	type name = va_arg(args, type);

/* Macro: get - 
 * Obtém um atributo dentro de uma classe
 */
#define get(att_name)\
	this.attributes[__get_attribute_index__(this, __LINE__, __FILE__, #att_name)]->_value

/* Macro: call - 
 * Realiza a chamada de um método dentro de uma classe
 */
#define call(obj, func, ...)\
	__realize_call__(obj, __LINE__, __FILE__, #func, ##__VA_ARGS__)

/**************
 * Estruturas *
 **************/
struct Class{
	Class *_super;
	char _name[__MAX_STR_LEN__];
	Method *methods[__MAX_MET__];
	Attribute *_attributes[__MAX_MET__];
};

struct Attribute{
	scope _visibility;
	char _type[__MAX_STR_LEN__];
	char _name[__MAX_STR_LEN__];
	generic _value;
};

struct Method{
	scope _visibility;
	char _name[__MAX_STR_LEN__];
	generic (*_function)();
};

struct Object{
	Class *_type;
	Attribute *attributes[__MAX_MET__];
};

/***********
 * Funções *
 ***********/
/*
 * __get_attribute_index__ - 
 * Recebe Object this, int _callLine_, char* _callFile_,char* att_name.
 * Busca pelo atributo de nome att_name no objeto this. Retorna um inteiro com o
 * indice do atributo, caso não encontre exibe uma mensagem de erro, e retorna -1
 */
static int __get_attribute_index__(Object this, int _callLine_, char* _callFile_,char* att_name){
	/*fprintf(stderr, "DEBUG: Procurando em %s o atributo %s.\n", this._type->_name, att_name);*/
	for(__i__=0; __i__<__MAX_MET__; __i__++){
		if(strcmp(att_name, (*this.attributes[__i__])._name)==0) return __i__;
	}
	fprintf(stderr, "Erro: A classe '%s' não possui um atributo '%s'.[Linha: %d : %s]\n", this._type->_name, att_name, _callLine_, _callFile_);
	return -1;
}
/*
 * __find_method_on_object__ - 
 * Recebe Object _obj_, int _callLine_, char* _callFile_, char* func, va_list args.
 * Busca pela função de nome func no objeto _obj_, passando args como argumento.
 * Devolve um generic com o retorno da função, ou exibe uma mensagem de erro e retorna
 * NULL caso haja qualquer problema.
 */
static generic __find_method_on_object__(Object _obj_, int _callLine_, char* _callFile_, char* func, va_list args){
	generic _ret;
	for(__i__=0;_obj_._type->methods[__i__]!=NULL && __i__<__MAX_MET__;__i__++){
		if(strcmp(_obj_._type->methods[__i__]->_name, func)==0){
			if(_obj_._type->methods[__i__]->_visibility==private){
				//printf("[%s -> Privado: %s-%s]\n", _obj_._type->methods[__i__]->_name, _obj_._type->_name, _scope_._type->_name);
				if(!strcmp(_obj_._type->_name, _scope_._type->_name)==0){
					fprintf(stderr, "Erro: A função '%s' é privada em '%s'.[Linha: %d]\n", func, _obj_._type->_name, _callLine_);
					return NULL;
				}
			}
			else if(_obj_._type->methods[__i__]->_visibility==protected){
				//printf("[%s -> Protegido: %s-%s]\n", _obj_._type->methods[__i__]->_name, _obj_._type->_name, _scope_._type->_name);
			}
			else{
				//printf("[%s -> Publico: %s-%s]\n", _obj_._type->methods[__i__]->_name, _obj_._type->_name, _scope_._type->_name);
			}

			_ret = (generic)_obj_._type->methods[__i__]->_function(_obj_, args);
			return _ret;
		}
	}// Se não encontra o método na classe filha, procura na super
	/*printf("Procurando na super de %s\n", _obj_._type->_name);*/
	if(strcmp(func, "__init__")==0 || strcmp(_obj_._type->_super->_name, "__OBJECT__")!=0){
		// Criamos uma instância da super
		Object* super = (Object*)malloc(sizeof(Object));
		super->_type = _obj_._type->_super;
		for(__i__=0;__i__<__MAX_MET__; __i__++){// Alocamos seus atributos
			super->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));
			//if((*_obj_.type._super)._attributes[__i__]==NULL) continue;
			super->attributes[__i__]->_visibility = _obj_.attributes[__i__]->_visibility;
			strncpy(super->attributes[__i__]->_type, _obj_.attributes[__i__]->_type, __MAX_STR_LEN__);
			strncpy(super->attributes[__i__]->_name, _obj_.attributes[__i__]->_name, __MAX_STR_LEN__);
			// Copiamos o valor dos atributos na super, permitindo modificação
			super->attributes[__i__]->_value = _obj_.attributes[__i__]->_value;
		}
		// Chamamos recursivamente o método passando a super
		_ret = __find_method_on_object__(*super, _callLine_, _callFile_, func, args);
		// Depois de pronto, desalocamos tudo
		for(__i__=0;__i__<__MAX_MET__; __i__++){
			// Repassamos os atributos redefidos na super para a filha, antes de desalocar
			_obj_.attributes[__i__]->_value = super->attributes[__i__]->_value;
			free(super->attributes[__i__]);
		}
		free(super);
		// Passamos o resultado
		return _ret;
		//return (generic) __find_method_on_class__(*_obj_.type._super, func);
	}
	fprintf(stderr, "Erro: A classe '%s' não possui a função '%s'.[Linha: %d : %s]\n", _obj_._type->_name, func, _callLine_, _callFile_);
	return NULL;
}
/*
 * __realize_call__ - 
 * Recebe Object *_obj, int _callLine_, char* _callFile_, char* func, ...
 * Faz o intemédio entre a macro 'call' e a função __find_method_on_object__.
 */
static generic __realize_call__(Object *_obj, int _callLine_, char* _callFile_, char* func, ...){
	_scope_ = *_obj;
	generic _ret;
	va_list args;
	va_start(args, func);
	_ret = __find_method_on_object__(_scope_, _callLine_, _callFile_, func, args);
	va_end(args);
	return _ret;
}


/*************************
 * Utilidades de Classes *
 *************************/
/*
 * __init__f - 
 * Não recebe argumentos. É o inicializador padrão de classes.
 */
static generic __init__f (void){return NULL;};
/* __init__ - Estrutura que define o método padrão de inicialização */
static Method __init__ = {protected, "__init__", &__init__f};
/* __OBJECT__ - Estrutura ao qual toda classe herda, para permitir uso de inicializador */
static Class __OBJECT__ = {NULL, "__OBJECT__", {&__init__}, {}};