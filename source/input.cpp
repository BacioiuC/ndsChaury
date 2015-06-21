#include <input.h>
#include <nds.h>
#include <iostream>
#include <lua.hpp>
#include <sstream>

using namespace std;
int tx;
int ty;

int getTouchPositionX(int _x)
{
	tx = _x;
}
int getTouchPositionY(int _y)
{
	ty = _y;
}
/*
 int handleTouch(int _tx, int _ty )
 {
 	iprintf("Touch x = %d\n", _tx);
	iprintf("Touch y = %d\n", _ty);
 }
 */ 
 


Input::Input( )
{
	
	touch_x = 2;
	touch_y = 2;
	touchState = false;
}

void Input::touchLoop()
{
	scanKeys();
	touchRead(&touch);
	pressed = keysDown();	
	held = keysHeld();		
	touch_x = touch.px;
	touch_y = touch.py;
	//cout << "PX IS: " << _px <<  " | PY IS: " << _py << endl;
	//cout << "PRessed: " << pressed << endl;
	if (held & KEY_TOUCH)
	{
		touchState = true;
	}
	else
		touchState = false;

}

int Input::getKeyHeld( )
{
	return held;
}

int Input::getKeyPressed( )
{
	return pressed;
}

bool Input::getTouchState( )
{
	return touchState;
}

int Input::getX( )
{
	//cout << "TX FUCKING IS: " << tx << endl;
	return touch_x;
}

int Input::getY( )
{
	//cout << "TY FUCKING IS: " << ty << endl;
	return touch_y;
}

//------------------ LUA REGS -------------------
/* Sprite Class Constructor */
int l_Input_constructor(lua_State * l)
{
 
    Input ** udata = (Input **)lua_newuserdata(l, sizeof(Input *));
    *udata = new Input();
 

    luaL_getmetatable(l, "luaL_Input");
 

    lua_setmetatable(l, -2);
 

    return 1;
}

Input * l_CheckInput(lua_State * l, int n)
{
    // This checks that the argument is a userdata 
    // with the metatable "luaL_Sprite"
    return *(Input **)luaL_checkudata(l, n, "luaL_Input");
}

int l_Input_getTouchState(lua_State * l)
{
	Input * input = l_CheckInput(l, 1);
	bool tState = input->getTouchState( );
	lua_pushboolean(l, tState);
	return 1;
}

int l_Input_touchLoop(lua_State * l)
{
	Input * input = l_CheckInput(l, 1);
	input->touchLoop();
	return 0;
}

/*
	Extremely Hacky! pushinteger fails on trying to push a int typecast from u16
	Push number doesn't halp us at all!
	My solution? Turn the output into a string, push it in the stack and convert 
	it to number from lua!

*/
int l_Input_getX(lua_State * l)
{
	Input * input = l_CheckInput(l, 1);
	std::string numberString;
	ostringstream convert;

	convert << input->getX( );
	
	numberString = convert.str( );
	//cout << "TX: " << input->getX() << endl;
	lua_pushstring(l, numberString.c_str() );
	return 1;
}

int l_Input_getY(lua_State * l)
{
	Input * input = l_CheckInput(l, 1);

	std::string numberString;
	ostringstream convert;

	convert << input->getY( );
	
	numberString = convert.str( );
	//cout << "TY: " << input->getY() << endl;
	lua_pushstring(l, numberString.c_str() ); //lua_pushinteger(l, input->getY() );
	return 1;
}


 
void RegisterInput(lua_State * l)
{
    luaL_Reg sFooRegs[] =
    {
        { "new", l_Input_constructor },
		{ "getX", l_Input_getX },
		{ "getY", l_Input_getY },
		{ "touchLoop", l_Input_touchLoop },
		{ "getTouchState", l_Input_getTouchState },
    };
 
    // Create a luaL metatable. This metatable is not 
    // exposed to Lua. The "luaL_Foo" label is used by luaL
    // internally to identity things.
    luaL_newmetatable(l, "luaL_Input");
 
    // Register the C functions _into_ the metatable we just created.
	luaL_setfuncs (l, sFooRegs, 0);
 
    // The Lua stack at this point looks like this:
    //     
    //     1| metatable "luaL_Foo"   |-1
    lua_pushvalue(l, -1);
 
    // The Lua stack at this point looks like this:
    //     
    //     2| metatable "luaL_Foo"   |-1
    //     1| metatable "luaL_Foo"   |-2
 
    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(l, -1, "__index");
 
    // The Lua stack at this point looks like this:
    //     
    //     1| metatable "luaL_Foo"   |-1
 
    // The luaL_Foo metatable now has the following fields
    //     - __gc
    //     - __index
    //     - add
    //     - new
 
    // Now we use setglobal to officially expose the luaL_Foo metatable 
    // to Lua. And we use the name "Foo".
    //
    // This allows Lua scripts to _override_ the metatable of Foo.
    // For high security code this may not be called for but 
    // we'll do this to get greater flexibility.
    lua_setglobal(l, "Input");
}