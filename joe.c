#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "table.h"

#define JOE_INT 0x01
#define JOE_TABLE 0x2
#define JOE_STRING 0x3
#define JOE_FUNC 0x4
#define JOE_NIL 0x5
#define JOE_ERROR 0x6
#define MAX_BUF_SIZE 1024
#define MAX_PARAM_BUFFER 1024

#define MAX_FUNC_NAME 70
#define MAX_FUNC_PARAMS 20
#define MAX_FUNC_INSTRS 100

typedef lm_hashtable jo_table ;
typedef lm_hashentry jo_entry ;

typedef struct 
{
    void *data;
    short type;
} value ;

value _nil = {.type = JOE_NIL, .data = NULL};
value *nil = &_nil;
value *symbol_table = NULL;
value *SYNTAX_ERROR = NULL;
value *BAD_TABLE = NULL;
value *BAD_STRING  = NULL;
value *BAD_FUNC  = NULL;

// API / Modules

void joe_log_value(value *v);
value* joe_new_string(char *buf, size_t size);
value* joe_new_int(int i);
value* joe_new_error(char *msg);
value* joe_new_table();
value* joe_put(value *tvalue, char *key, value *val);
value* joe_get(value *tvalue, char *key);
value *joe_eval(char *buff);
value* _joe_get_string(char *buff, int len) ;
value* _joe_get_int(char *buff, int len) ;
value* _joe_get_table(char *buff, int len) ;
void _joe_clear_value(value *v);
void joe_clear_value(value *v); 
void joe_init();
void joe_cleanup();



// @Implementation
void joe_init() 
{
    symbol_table = joe_new_table();
    SYNTAX_ERROR = joe_new_error("^ invalid syntax");
    BAD_TABLE = joe_new_error("^ invalid table");
    BAD_STRING = joe_new_error("^ invalid string");
    BAD_FUNC = joe_new_error("^ invalid function");
}

void joe_cleanup()
{
    joe_clear_value(symbol_table);
    joe_clear_value(SYNTAX_ERROR);
    joe_clear_value(BAD_TABLE);
    joe_clear_value(BAD_STRING);
    joe_clear_value(BAD_FUNC);
}

value* joe_new_string(char *buf, size_t len) 
{
    value *v = (value*)malloc(sizeof(v));
    v->type = JOE_STRING;
    char *data = (char*)malloc(sizeof(char) * (len+1));
    v->data = data;
    
    size_t i = 0;
    for (;i<len || data[i]; i++) {
        data[i] = buf[i];
    }
    
    data[i] = '\0';
    return v;
}

value* joe_new_table() 
{
    value *v = (value*)malloc(sizeof(v));
    v->type = JOE_TABLE;
    v->data = lm_hashtable_new();
    return v;
}

value* joe_new_int(int a) 
{
    value *v = (value*)malloc(sizeof(v));
    v->type = JOE_INT;
    int *data = (int*)malloc(sizeof(int));
    data[0] = a;
    v->data = data;
    return v;
}

value* joe_new_error(char *msg) {
    value *e = joe_new_string(msg, strlen(msg));
    e->type = JOE_ERROR;
    return e;
}

value* joe_put(value *tvalue, char *key, value *val) {
    if (tvalue->type == JOE_TABLE) {
        jo_table *t = (jo_table*)tvalue->data;
        lm_hashtable_put(t, key, val);
        return val;
    }
    return tvalue;
}

value* joe_get(value *tvalue, char *key) {
    if (tvalue->type == JOE_TABLE) {
        value *v;
        jo_table *t = (jo_table*)tvalue->data;
        jo_entry *e = lm_hashtable_get(t, key);
        return (e != NULL) ? e->value : nil;
    }

    return tvalue;
}

value* joe_new_func()
{
    value *v = (value*)malloc(sizeof(v));
    v->type = JOE_FUNC;
    v->data = nil;
    return v;
}

void _joe_clear_entry(jo_entry *e) {
    value *v = (value*)e->value;
    if (v != NULL)
        joe_clear_value(v);
}

void joe_clear_value(value *v) {
    switch (v->type) {
        case JOE_STRING:
        case JOE_ERROR:
        case JOE_INT:
            free(v->data);
            break;
        case JOE_TABLE:
            lm_hashtable_free_with((jo_table*)v->data, _joe_clear_entry);
            break;
        default:
            return;
    }

    free(v);
}

void joe_log_value(value *v) {
    switch (v->type) {
        case JOE_STRING:
            printf("String: %s\n", (char*)v->data);
            break;
        case JOE_ERROR:
            printf("%s\n", (char*)v->data);
            break;
        case JOE_INT:
            printf("Integer: %d\n", *((int*)v->data));
            break;
        case JOE_TABLE:
            printf("Table: {}\n");
            break;
        case JOE_FUNC:
            printf("<function at %p>\n", v);
            break;
        case JOE_NIL:
            printf("nil\n");
            break;
        default:
            return;
    }
}

value* _joe_get_function(char *buff, int len);

value *joe_eval(char *buff) {
    size_t len = strlen(buff);
    if (len == 0)
        return nil;
    char t = buff[0];

    if (t == '"') {
        return _joe_get_string(buff, len);
    } else if (t== '{') {
        return _joe_get_table(buff, len);
    } else if (t >= '0' && t <= '9') {
        return _joe_get_int(buff, len);
    } else if (t >= 'a' && t <= 'z') {
        return _joe_get_function(buff, len);
    } else if(strcmp(buff,"nil")==0) {
        return nil;
    } else {
        return SYNTAX_ERROR;
    }
}

typedef struct {
    char name[MAX_FUNC_NAME];
    value* params[MAX_FUNC_PARAMS];
    int instrs[MAX_FUNC_INSTRS];
    int pr;
    int ps;
    value* (*native)(value* params[]);
} joe_func ;

void joe_init_function_type(joe_func *ft);

void joe_init_func(joe_func *ft) {
    int i=0;
    for (;i<MAX_FUNC_PARAMS;i++)
        ft->params[i]=nil;

    i =0;
    for (;i<MAX_FUNC_INSTRS;i++)
        ft->instrs[i]=0;
    ft->pr = 0;
    ft->ps = 0;
}

value* _joe_get_function(char *buff, int len) {
    int v=0, k=0, s=1;
    joe_func f;
    joe_init_func(&f);
    char *name = f.name;
    char param[MAX_PARAM_BUFFER];

    while (v<len) {
        char c=buff[v];
        if (c== ' ') {
            v++;
            continue;
        }

        if ((c>='a' && c<='z') || c=='_') {
            name[k++]=c;
            if (s!=1) {
                return BAD_FUNC;
            }
        } else if (c=='(') {
            name[k]='\0';
            k=0;
            if (s==3) {
                return BAD_FUNC;
            }
            s = 2;
        } else if (c==')') {
            if (s!=2) {
                return BAD_FUNC;
            }
            s = 3;

            param[k] = '\0';
            value *v = joe_eval(param);
            if (v->type == JOE_ERROR) {
                return v;
            }
            f.params[f.ps]=v;
            f.ps++;
            k=0;
        } else {
            if (s == 2) {
                if (c==',') {
                    param[k] = '\0';
                    value *v = joe_eval(param);
                    if (v->type == JOE_ERROR) {
                        return v;
                    }
                    f.params[f.ps]=v;
                    f.ps++;
                    k=0;
                } else {
                    param[k++] = c;
                }
            }  else {
                return SYNTAX_ERROR;
            }
        }
        v += 1;
    }

    if (s!=3) return SYNTAX_ERROR;
    return nil;
}

value* _joe_get_string(char *buf, int len) {
    char *nbuf = strdup(buf+1);
    len -= 1;
    int v=0;
    while (v<len) {
        if (nbuf[v] == '"' && v!= (len-1)) {
            return BAD_STRING;
        }
        v++;
    }

    if (nbuf[len-1] != '"') {
        return BAD_STRING;
    }

    nbuf[len-1] = '\0';
    len -= 1;
    return joe_new_string(nbuf, len);
}

value* _joe_get_int(char *buff, int len) {
    int i = atoi(buff);
    value *v = joe_new_int(i);
    return v;
}

value* _joe_get_table(char *buff, int len) {
    size_t v=0;
    while (v<len) {
        if (buff[v] == ' ' && v != (len-1)) {
            return BAD_TABLE;
        }
        v++;
    }

    if (buff[len-1] != '}') {
        return BAD_TABLE;
    }

    return joe_new_table();
}

int main(int argc, char *argv[])
{
    joe_init();
    printf("welcome to joe.\\h for help and \\q for quiting\nhave fun\n");

    while (1) {
        printf("joe> ");
        char *buff = readline(NULL);

        if (!buff) {
            break;
        }else if (!*buff) {
            continue;
        } else if (strcmp(buff,"\\q") == 0)  {
            free(buff);
            break;
        } else if (strcmp(buff,"\\h") == 0)  {
            printf(
                    "a string:   \"hello, world\"\n"
                    "an integer: 1234545\n"
                    "a table:    {}\n"
                  );
            free(buff);
            continue;
        }

        value *val = joe_eval(buff);
        if (val->type == JOE_ERROR) {
            printf("%s\n", buff);
        }

        joe_log_value(val);

        if (val->type != JOE_NIL && val->type != JOE_ERROR) {
            //XXX
            //joe_clear_value(val);
        }
        val = NULL;

        free(buff);
    }

    joe_cleanup();
    return 0;
}

