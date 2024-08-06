#include "../include/luatemplate.h"
#include <string.h>

extern int luaopen_luatemplate(lua_State *L);

const char* lua_snippet =   "local msg = {}\n"
                            "local function collect(text)\n"
                            "    msg[#msg + 1] = text\n"
                            "end\n"
                            "local ctx = template.context()\n"
                            "ctx:renderFile(file_path, args, collect)\n"
                            "result = table.concat(msg)";

void lt_loadlib(lua_State *L) {
    luaL_requiref(L, "template", luaopen_luatemplate, 1);
    lua_pop(L, 1);
}

char* lt_render(lua_State *L, const char *template_path, lt_arg *args, int nargs, int *len) {
    lua_createtable(L, 0, nargs);

    if (nargs > 0) {
        for (int i = 0; i < nargs; i++) {
            lua_pushstring(L, args[i].name);
            switch (args[i].value.type) {
                case LT_ARG_TYPE_STRING:
                    lua_pushstring(L, args[i].value.v.str);
                    break;
                case LT_ARG_TYPE_NUMBER:
                    lua_pushnumber(L, args[i].value.v.num);
                    break;
                default:
                    lua_pushnil(L);
                    break;
            }
            lua_settable(L, -3);
        }
    }

    lua_setglobal(L, "args");

    lua_pushstring(L, template_path);
    lua_setglobal(L, "file_path");

    luaL_dostring(L, lua_snippet);

    lua_getglobal(L, "result");
    const char *result = lua_tostring(L, -1);
    if (result == NULL) {
        return NULL;
    }

    *len = strlen(result);
    return strdup(result);
}
