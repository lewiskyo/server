#ifndef LUAVM
#define LUAVM
extern "C"{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <assert.h>
#include <iostream>

using namespace std;

class LuaVm{
    public:
        void init();
    public:
        static int _cb(LuaVm* vm, int type, int session, int source, const void* msg, int sz);

        static int traceback(lua_State* L);
        static int lcallback(lua_State* L);
        static int lcast(lua_State* L);
    private:
        void registFuncToLua();
    private:
        struct lua_State *L;
        
};

#endif 
