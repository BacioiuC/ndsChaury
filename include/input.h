#ifndef INPUT_H
#define INPUT_H

#include <luascript.h>
#include <nds/arm9/image.h>
#include <nds.h>
#include <lua.hpp>


class Input {
	public:
		Input( );
		~Input( );
		int touch_x;
		int touch_y;
		bool touchState;
		void touchLoop();
		int touchPressed( );
		int keysPressed( );
		int keysLoop( );
		int getX( );
		int getY( );
		touchPosition touch;
};

//int touchLoop(int _px, int _py);
int getTouchPositionX(int _x);
int getTouchPositionY(int _y);
int retTX( );
int retTY( );
int l_Input_getX(lua_State * l);
int l_Input_getY(lua_State * l);
int l_Input_touchLoop(lua_State * l);
void RegisterInput(lua_State * l);


#endif