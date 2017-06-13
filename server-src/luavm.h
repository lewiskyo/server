#ifndef LUAVM
#define LUAVM
extern "C"{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <iostream>

using namespace std;

class LuaVm{
    public:
        void init();
    private:
        struct LuaState *L;
}



#endif 
