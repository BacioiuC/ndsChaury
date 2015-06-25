#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <luascript.h>
#include <nds/arm9/image.h>
#include <lua.hpp>
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <glWrapper.h>
#include <list>

using namespace std;

class spriteBatch {
	public:
		struct spriteData {
			Sprite* sprite;
			int x;
			int y;
			int z;
			int width;
			int height;
		};
		spriteBatch( );
		~spriteBatch( );
		list<spriteData> batchList;
		bool add(Sprite* mySprite, int _x, int _y, int _width, int _height, int _z);
		int x;
		int y;
		int width;
		int height;
		int z;
		void render( );
		void update(Sprite* mySprite, int _x, int _y, int _z);
};

void RegisterSpriteBatch(lua_State * l);

#endif