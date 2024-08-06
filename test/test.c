#include <luatemplate.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lt_loadlib(L);

    lt_arg args[] = {
        {"title", {.type = LT_ARG_TYPE_STRING, .v = {.str = "Webdevs are WEEPING"}}},
        {"a", {.type = LT_ARG_TYPE_NUMBER, .v = {.num = 6}}},
    };

    int len;
    char* result = lt_render(L, (argc == 2) ? argv[1] : "sample.lt", args, 2, &len);
    if (result == NULL) {
        printf("Failed to render template\n");
        return 1;
    }

    printf("%s\n", result);
    
    free(result);
    lua_close(L);
    return 0;
}
