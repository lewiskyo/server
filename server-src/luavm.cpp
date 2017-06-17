#include "luavm.h"

int LuaVm::traceback(lua_State* L){
    const char *msg = lua_tostring(L,-1);
    if (msg)
        luaL_traceback(L,L,msg,1);
    else 
        lua_pushliteral(L, "(no message)");

    return 1;
}

int LuaVm::lcallback(lua_State* L){
    luaL_checktype(L,1,LUA_TFUNCTION);
    lua_settop(L,1);
    lua_rawsetp(L, LUA_REGISTRYINDEX, (void*)LuaVm::_cb); 
    return 0;
}

int LuaVm::lcast(lua_State* L){
    const char *msg = lua_tostring(L,-1);
    if (msg)
        cout << "cast message: " << msg << endl;
    else 
        cout << "no message in cast" << endl;

    return 0;
}
void LuaVm::registFuncToLua(){
    lua_pushcfunction(L, lcallback);
    lua_setglobal(L, "CALLBACK");

    lua_pushcfunction(L, lcast);
    lua_setglobal(L, "CAST");
}

int LuaVm::_cb(LuaVm* vm, int type, int session, int source, const void* msg, int sz){
   lua_State *L = vm->L;
   int trace = 1;
   int r;
   int top = lua_gettop(L);
   if (top == 0){
       lua_pushcfunction(L, LuaVm::traceback);
       lua_rawgetp(L, LUA_REGISTRYINDEX, (void*)LuaVm::_cb);
   } else {
       assert( r == 2);
   }
   lua_pushvalue(L, 2);

   lua_pushinteger(L, type);
   //lua_pushlightuserdata(L, (char*) msg);
   lua_pushstring(L, (char*) msg);
   lua_pushinteger(L, sz);
   lua_pushinteger(L, session);
   lua_pushinteger(L, source);

   r = lua_pcall(L,5,0,trace);
   
   if (r == LUA_OK)
       return 0;

   switch(r) {
       case LUA_ERRRUN:
           printf("lua script err: traceback: %s\n", lua_tostring(L, -1));
           break;
   };

   lua_pop(L,1);
   return 0;

}
void LuaVm::init(){
    L = luaL_newstate();
    lua_gc(L,LUA_GCSTOP,0);
    luaL_openlibs(L);
    registFuncToLua();

    // init cb
    const char *path = "./lua-script/?.lua;./lua-script/?/?.lua";
    lua_pushstring(L, path);
    lua_setglobal(L,"LUA_PATH");
    
    const char *cpath = "./lua-clib/?.so;";
    lua_pushstring(L, cpath);
    lua_setglobal(L,"LUA_CPATH");

    lua_pushcfunction(L, LuaVm::traceback);
    assert(lua_gettop(L) == 1);

    const char *loader = "./lua-script/loader.lua";

    int r = luaL_loadfile(L, loader);
    if (r != LUA_OK) {
        cout <<"can not load loader, reason: " <<  lua_tostring(L,-1) << endl;
        return;
    }

    const char *mainfile = "./lua-script/back/main.lua";
    lua_pushstring(L,mainfile);

    r = lua_pcall(L,1,0,1);
    if (r != LUA_OK) {
        cout << "lua loader error: reason: " << lua_tostring(L, -1) << endl;
        return;
    }

    lua_settop(L,0);

    lua_gc(L, LUA_GCRESTART, 0);
}
