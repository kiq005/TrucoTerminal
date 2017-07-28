#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_MET 256
#define MAX_LEN 64
#define generic void*
typedef enum{private, public, protected} scope;

typedef struct Class Class;
typedef struct Attribute Attribute;
typedef struct Method Method;
typedef struct Object Object;
generic __realize_call__(Object _obj_, char* func, ...);
generic __find_method_on_object__(Object _obj_, char* func, va_list args);

static int __i__;
static Object _scope_;

#define class(name, ...) Class name = {NULL, #name, __VA_ARGS__}
#define extends(name, super, ...) Class name = {&super, #name, __VA_ARGS__}
#define instanciate(name, _type_) \
	Object* name = (Object*)malloc(sizeof(Object));\
	name->type = _type_;\
	for(__i__=0;__i__<MAX_MET; __i__++){\
		name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
		if(_type_._attributes[__i__]==NULL) continue; \
		name->attributes[__i__]->_visibility = _type_._attributes[__i__]->_visibility;\
		strncpy(name->attributes[__i__]->_type, _type_._attributes[__i__]->_type, MAX_LEN);\
		strncpy(name->attributes[__i__]->_name, _type_._attributes[__i__]->_name, MAX_LEN);\
		name->attributes[__i__]->_value = NULL;\
	}
	
#define function(visibility, name, cmd) \
	generic _##name (Object this, va_list args){cmd}; Method name = {visibility, #name, &_##name}
#define var(visibility, type, name) \
	Attribute name = {visibility, #type, #name};
#define get(att_name)\
	this.attributes[__get_attribute_index__(this, #att_name)]->_value;
#define set(att_name, __value__)\
	this.attributes[__get_attribute_index__(this, #att_name)]->_value = (generic)__value__;

struct Class{
	Class *_super;
	char _name[MAX_LEN];
	Method *methods[MAX_MET];
	Attribute *_attributes[MAX_MET];
};

struct Attribute{
	scope _visibility;
	char _type[MAX_LEN];
	char _name[MAX_LEN];
	generic _value;
};

struct Method{
	scope _visibility;
	char _name[MAX_LEN];
	generic (*_function)();
};

struct Object{
	Class type;
	Attribute *attributes[MAX_MET];
};

int __get_attribute_index__(Object this, char* att_name){
	for(__i__=0; __i__<MAX_MET; __i__++){
		if(strcmp(att_name, (*this.attributes[__i__])._name)==0) return __i__;
	}
	fprintf(stderr, "Erro: A classe '%s' não possui um atributo '%s'.\n", this.type._name, att_name);
	return -1;
}

/* Esta função não é mais utilizada, pois não permite passagem de argumentos
 para uma super classe. Esta aqui somente para consultas, e logo deverá ser
 apagada.
*/
generic __find_method_on_class__(Class _class_, char* func, ...){
	for(__i__=0;_class_.methods[__i__]!=NULL && __i__<MAX_MET;__i__++){
		if(strcmp(_class_.methods[__i__]->_name, func)==0){
			va_list args;
			generic _ret;
			if(_class_.methods[__i__]->_visibility==private){
				if(strcmp(_class_._name, _scope_.type._name)==0){
					_class_.methods[__i__]->_function();
					return NULL;
				}
				fprintf(stderr, "Erro: A função '%s' é privada em '%s'.\n", func, _class_._name);
				return NULL;
			}
			va_start(args, func);
			_ret = (generic) _class_.methods[__i__]->_function(args);
			va_end(args);
			return _ret;
		}
	}// Se não encontra o método na classe filha, procura na super
	if(_class_._super!=NULL){
		return __find_method_on_class__(*_class_._super, func);
	}
	fprintf(stderr, "Erro: Não é possível chamar a função '%s' em '%s'.\n", func, _class_._name);
	return NULL;
}

generic __find_method_on_object__(Object _obj_, char* func, va_list args){
	generic _ret;
	for(__i__=0;_obj_.type.methods[__i__]!=NULL && __i__<MAX_MET;__i__++){
		if(strcmp(_obj_.type.methods[__i__]->_name, func)==0){
			if(_obj_.type.methods[__i__]->_visibility==private){
				if(!strcmp(_obj_.type._name, _scope_.type._name)==0){
					fprintf(stderr, "Erro: A função '%s' é privada em '%s'.\n", func, _obj_.type._name);
					return NULL;
				}
			}
			_ret = (generic)_obj_.type.methods[__i__]->_function(_obj_, args);
			return _ret;
		}
	}// Se não encontra o método na classe filha, procura na super
	if(_obj_.type._super!=NULL){
		// Criamos uma instância da super
		Object* super = (Object*)malloc(sizeof(Object));
		super->type = *_obj_.type._super;
		for(__i__=0;__i__<MAX_MET; __i__++){// Alocamos seus atributos
			super->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));
			//if((*_obj_.type._super)._attributes[__i__]==NULL) continue;
			super->attributes[__i__]->_visibility = _obj_.attributes[__i__]->_visibility;
			strncpy(super->attributes[__i__]->_type, _obj_.attributes[__i__]->_type, MAX_LEN);
			strncpy(super->attributes[__i__]->_name, _obj_.attributes[__i__]->_name, MAX_LEN);
			// Copiamos o valor dos atributos na super, permitindo modificação
			super->attributes[__i__]->_value = _obj_.attributes[__i__]->_value;
		}
		// Chamamos recursivamente o método passando a super
		_ret = __find_method_on_object__(*super, func, args);
		// Depois de pronto, desalocamos tudo
		for(__i__=0;__i__<MAX_MET; __i__++){
			// Repassamos os atributos redefidos na super para a filha, antes de desalocar
			_obj_.attributes[__i__]->_value = super->attributes[__i__]->_value;
			free(super->attributes[__i__]);
		}
		free(super);
		// Passamos o resultado
		return _ret;
		//return (generic) __find_method_on_class__(*_obj_.type._super, func);
	}
	fprintf(stderr, "Erro: Não é possível chamar a função '%s' em '%s'.\n", func, _obj_.type._name);
	return NULL;
}

generic __realize_call__(Object _obj, char* func, ...){
	generic _ret;
	va_list args;
	va_start(args, func);
	_ret = __find_method_on_object__(_obj, func, args);
	va_end(args);
	return _ret;
}

#define call(obj, func, ...)\
	__realize_call__(_scope_=*obj, #func, ##__VA_ARGS__)
