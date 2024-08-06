#ifndef _LUATEMPLATE_C_API_H
#define _LUATEMPLATE_C_API_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef enum _lt_arg_type {
    LT_ARG_TYPE_STRING,
    LT_ARG_TYPE_NUMBER,
    // LT_ARG_TYPE_TABLE,       // v
    // LT_ARG_TYPE_FUNCTION,    // idk, test this
} lt_arg_type;

typedef struct _lt_lua_value {
    lt_arg_type type;
    union {
        char* str;
        double num;
        // lua_CFunction func;
        // struct {
        //     char* key;
        //     struct _lt_lua_value* value;
        // } table;
    } v;
} lt_lua_value;

typedef struct _lt_arg {
    char* name;
    lt_lua_value value;
} lt_arg;

void lt_loadlib(lua_State *L);
char* lt_render(lua_State *L, const char *template, lt_arg *args, int nargs, int *len);

#endif
