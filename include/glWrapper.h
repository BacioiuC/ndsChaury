#ifndef GLWRAPPER_H
#define GLWRAPPER_H

#include <luascript.h>
#include <nds/arm9/image.h>
#include <lua.hpp>

class Sprite {
	public:
		Sprite( );
		~Sprite( );
		int x;
		int y;
		int z;
		int layer; // layer is basically Z :D
		void newSprite(int _x, int _y, int _width, int _height, int _z, int imgToUse, int texSize);
		int width;
		int height;
		int size;
		void update( );
		
		void setX( int _x );
		int getX( );
		void setY( int _y );
		int getY( );
		
		int getSize( );
		int getWidth( );
		int getHeight( );
		void setSize( int _width, int _height );
		void printSomething( );
		int texID = 0;
		
		void setTexture(int _texID);
	private:
		
		void render( );
};

int initGL ( );
int LoadGLTextures();

// LUA Bindings here
int l_initGL(lua_State * L);
int l_RandomNumber(lua_State * L);
/*int l_Sprite_constructor(lua_State * l);

Sprite * l_CheckSprite(lua_State * l, int n);
int l_Sprite_newSprite(lua_State * l);
int l_Sprite_update(lua_State * l);*/
void RegisterFoo(lua_State * l);

#endif