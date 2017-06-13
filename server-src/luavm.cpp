#include "luavm.h"

void LuaVm::init(){
    L = luaL_newstate();
    luaL_openlibs(L);
    
    // init cb
    
    // init loader ==> bootstrap ==> require lua_clib ==> reg cb

