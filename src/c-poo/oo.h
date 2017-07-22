#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_MET 256
#define MAX_LEN 64
typedef enum{private, public, protected} scope;

typedef struct Class Class;
typedef struct Attribute Attribute;
typedef struct Method Method;
typedef struct Object Object;
void __find_method_on_class__(Class _class_, char* func);

static Class _scope_;

#define generic void*
#define class(name, ...) Class name = {NULL, #name, __VA_ARGS__}
#define extends(name, super, ...) Class name = {&super, #name, __VA_ARGS__}
#define function(visibility, name, cmd) \
	generic _##name (){cmd}; Method name = {visibility, #name, &_##name}
#define instanciate(name, _type) \
	Object* name = (Object*)malloc(sizeof(Object));\
	name->type = _type;

struct Class{
	Class *_super;
	char _name[MAX_LEN];
	Method *methods[MAX_MET];
	Attribute *attributes[MAX_MET];
};

struct Attribute{
	scope _visibility;
	char _name[MAX_LEN];

};

struct Method{
	scope _visibility;
	char _name[MAX_LEN];
	generic (*_function)();
};

struct Object{
	Class type;
	void (*_get)(char* name);
	void (*_set)(char* name, void *value);
	void (*_call)(char* name, void *args);
};

void __find_method_on_class__(Class _class_, char* func){
	int __i__;
	for(__i__=0;_class_.methods[__i__]!=NULL && __i__<MAX_MET;__i__++){
		if(strcmp(_class_.methods[__i__]->_name, func)==0){
			if(_class_.methods[__i__]->_visibility==private){
				if(strcmp(_class_._name, _scope_._name)==0){
					_class_.methods[__i__]->_function();
					return;
				}
				fprintf(stderr, "Erro: A função '%s' é privada em '%s'.\n", func, _class_._name);
				return;
			}
			_class_.methods[__i__]->_function();
			return;
		}
	}// Se não encontra o método na classe filha, procura na super
	if(_class_._super!=NULL){
		__find_method_on_class__(*_class_._super, func);
		return;
	}
	fprintf(stderr, "Erro: Não é possível chamar a função '%s' em '%s'.\n", func, _class_._name);
}

#define call(obj, func) \
	__find_method_on_class__(_scope_=obj->type, #func)
