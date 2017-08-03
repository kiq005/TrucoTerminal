#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <stdint.h>

#define MAX_MET 256
#define MAX_LEN 64
#define generic void*
typedef enum{private, public, protected} scope;

typedef struct Class Class;
typedef struct Attribute Attribute;
typedef struct Method Method;
typedef struct Object Object;
int __get_attribute_index__(Object this, char* att_name);
generic __realize_call__(Object _obj_, char* func, ...);
generic __find_method_on_object__(Object _obj_, char* func, va_list args);

static int __i__, __j__, __methods__=0;
static Object _scope_;
static Class _super_;

#define class(name, ...) Class name = {NULL, #name, __VA_ARGS__}
#define extends(name, super, ...) Class name = {&super, #name, __VA_ARGS__}
/*Precisamos trocar o modo de definição de atributos para uma variavel em loop while(!=null)
 assim conseguiremos herdar corretamente de classes avós!!!*/
#define instanciate(_type_, name) \
	Object* name = (Object*)malloc(sizeof(Object));\
	name->_type = &_type_;\
	for(__i__=0;__i__<MAX_MET; __i__++){\
		name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
		if(_type_._attributes[__i__]==NULL){\
			if(_type_._super==NULL) continue;\
			break;\
		}\
		name->attributes[__i__]->_visibility = _type_._attributes[__i__]->_visibility;\
		strncpy(name->attributes[__i__]->_type, _type_._attributes[__i__]->_type, MAX_LEN);\
		strncpy(name->attributes[__i__]->_name, _type_._attributes[__i__]->_name, MAX_LEN);\
		name->attributes[__i__]->_value = NULL;\
	}\
	/*Herdando atributos de classes superiores*/\
	if(name->_type!=NULL){\
		_super_ = *name->_type;\
		while(1){\
			/*printf("DEBUG: vendo atributos de %s.\n", _super_._name);*/\
			for(__j__=0;__i__<MAX_MET && _super_._attributes[__j__]!=NULL; __i__++, __j__++){\
				name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
				if(_super_._attributes[__j__]==NULL) continue; \
				name->attributes[__i__]->_visibility = _super_._attributes[__j__]->_visibility;\
				strncpy(name->attributes[__i__]->_type, _super_._attributes[__j__]->_type, MAX_LEN);\
				strncpy(name->attributes[__i__]->_name, _super_._attributes[__j__]->_name, MAX_LEN);\
				name->attributes[__i__]->_value = NULL;\
				/*printf("DEBUG: Adicionado %s á %s.\n", name->attributes[__i__]->_name, #name);*/\
			}\
			if(_super_._super==NULL) break;\
			_super_ = *_super_._super;\
		}\
	}\
	/*Finaliza instanciação*/\
	for(;__i__<MAX_MET;__i__++){\
		name->attributes[__i__]=(Attribute*)malloc(sizeof(Attribute));\
	}


#define function(visibility, name, cmd) \
	generic _##name (Object this, va_list args){cmd}; Method name = {visibility, #name, &_##name}
#define _override_function_(visibility, _name_, nameidx, _class_, cmd) \
	generic _##_name_##nameidx (Object this, va_list args){cmd}; Method _o_##_name_##nameidx= {public, #_name_, &_##_name_##nameidx};\
	/*GNU C*/\
	__attribute__((constructor)) _init_##_name_##nameidx(){\
		_o_##_name_##nameidx._visibility = _name_._visibility;\
		for(__i__=0; __i__<MAX_MET; __i__++){ \
			if(_class_.methods[__i__]==NULL){ \
				_class_.methods[__i__]=&_o_##_name_##nameidx; \
				break; \
			} \
		} \
	};
#define override(_class_, name, cmd) \
	_override_function_(name._visibility, name, __methods__, _class_, cmd)
#define var(visibility, type, name) \
	Attribute name = {visibility, #type, #name};
#define get(att_name)\
	this.attributes[__get_attribute_index__(this, #att_name)]->_value;
#define set(att_name, __value__)\
	/*printf("DEBUG: Estamos na classe %s.\n", this._type->_name);*/\
	this.attributes[__get_attribute_index__(this, #att_name)]->_value = __value__;
	
#define delete(_obj_)\
	for(__i__=0; __i__<MAX_MET; __i__++){\
		free(_obj_->attributes[__i__]);\
	}\
	free(_obj_)

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
	Class *_type;
	Attribute *attributes[MAX_MET];
};

int __get_attribute_index__(Object this, char* att_name){
	/*fprintf(stderr, "DEBUG: Procurando em %s o atributo %s.\n", this._type->_name, att_name);*/
	for(__i__=0; __i__<MAX_MET; __i__++){
		if(strcmp(att_name, (*this.attributes[__i__])._name)==0) return __i__;
	}
	fprintf(stderr, "Erro: A classe '%s' não possui um atributo '%s'.\n", this._type->_name, att_name);
	return -1;
}

generic __find_method_on_object__(Object _obj_, char* func, va_list args){
	generic _ret;
	for(__i__=0;_obj_._type->methods[__i__]!=NULL && __i__<MAX_MET;__i__++){
		if(strcmp(_obj_._type->methods[__i__]->_name, func)==0){
			if(_obj_._type->methods[__i__]->_visibility==private){
				if(!strcmp(_obj_._type->_name, _scope_._type->_name)==0){
					fprintf(stderr, "Erro: A função '%s' é privada em '%s'.\n", func, _obj_._type->_name);
					return NULL;
				}
			}
			_ret = (generic)_obj_._type->methods[__i__]->_function(_obj_, args);
			return _ret;
		}
	}// Se não encontra o método na classe filha, procura na super
	/*printf("Procurando na super de %s\n", _obj_._type->_name);*/
	if(_obj_._type->_super!=NULL){
		// Criamos uma instância da super
		Object* super = (Object*)malloc(sizeof(Object));
		super->_type = _obj_._type->_super;
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
	fprintf(stderr, "Erro: A classe '%s' não possui a função '%s'.\n", _obj_._type->_name, func);
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
