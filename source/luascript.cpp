#include "luascript.h"



LuaScript::LuaScript(const std::string& filename) {
    L = luaL_newstate();


   
}

LuaScript::~LuaScript() {
	if(L) lua_close(L);
}

bool LuaScript::GetExecutionStatus( )
{
    return LualExecutionIsOk;
}

void LuaScript::loadFile(const std::string& fileName)
{

    int status = luaL_loadfile(L, fileName.c_str());
    if (status) {
        std::cout<<"ERROR RIGHT HERE"<<std::endl;
         LualExecutionIsOk = false;
    }
    else
    {
        std::cout<<"FORWARD"<<std::endl;

        int error = lua_pcall(L, 0, 0, 0);
        std::cout << "Error is: "<<error<<std::endl;
        if( error != 0 )
        {
          LualExecutionIsOk = false;
        }
        else
        {
           LualExecutionIsOk = true;
            
        }
       
         if(L) luaL_openlibs(L);
    }



}

void LuaScript::printError(const std::string& variableName, const std::string& reason) {
	std::cout<<"Error: can't get ["<<variableName<<"]. "<<reason<<std::endl;
}

lua_State* LuaScript::getLuaState( )
{
	return L;
}

static int traceback(lua_State *L) {
    lua_getfield(L, LUA_RIDX_GLOBALS, "debug");
    lua_getfield(L, -1, "traceback");
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 2);
    lua_call(L, 2, 1);
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    return 1;
}

void LuaScript::pushFunction( lua_CFunction f, std::string globalName)
{
	lua_pushcfunction(L, f);
	lua_setglobal(L, globalName.c_str());
}


void LuaScript::getGlobal(std::string global)
{
	lua_getglobal(L, global.c_str());
}

int LuaScript::getTop()
{
	return lua_gettop(L);
}

void LuaScript::call( )
{
	lua_call(L, 0, 0);
}

bool LuaScript::isFunction()
{
	return lua_isfunction(L,this->getTop());
}

std::vector<int> LuaScript::getIntVector(const std::string& name) {
    std::vector<int> v;
    lua_gettostack(name.c_str());
    if(lua_isnil(L, -1)) { // array is not found
        return std::vector<int>();
    }
    lua_pushnil(L);
    while(lua_next(L, -2)) {
        v.push_back((int)lua_tonumber(L, -1));
        lua_pop(L, 1);
    }
    clean();
    return v;
}

std::vector<std::string> LuaScript::getTableKeys(const std::string& name) {
    std::string code = 
        "function getKeys(name) "
        "s = \"\""
        "for k, v in pairs(_G[name]) do "
        "    s = s..k..\",\" "
        "    end "
        "return s "
        "end"; // function for getting table keys
    luaL_loadstring(L, 
        code.c_str()); // execute code
    lua_pcall(L,0,0,0);
    lua_getglobal(L, "getKeys"); // get function
    lua_pushstring(L, name.c_str());
    lua_pcall(L, 1 , 1, 0); // execute function
    std::string test = lua_tostring(L, -1);
    std::vector<std::string> strings;
    std::string temp = "";
    std::cout<<"TEMP:"<<test<<std::endl;
    for(unsigned int i = 0; i < test.size(); i++) {     
        if(test.at(i) != ',') {
            temp += test.at(i);
        } else {
            strings.push_back(temp);
            temp= "";
        }
    }
    clean();
    return strings;
}
