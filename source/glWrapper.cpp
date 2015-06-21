#include <luascript.h>
#include <lua.hpp>
#include <glWrapper.h>
#include <nds.h>
#include <stdlib.h>
#include <time.h>       /* time */
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <filesystem.h>
#include <nds/arm9/image.h>

#include <typeinfo>
// Graphics includes
#include "slot_pcx.h"
#include "default_tex_pcx.h"
#include "zapah_pcx.h"
#include "twitter_pcx.h"
#include "bg_top_pcx.h"
#include "bg_bottom_pcx.h"
#include "inventory_bottom_header_pcx.h"

int textureID;
using namespace std;

bool	light;				// Lighting ON/OFF ( NEW )


float LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
float LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

//-------------------------------------------------------
// set up a 2D layer construced of bitmap sprites
// this holds the image when rendering to the top screen
//-------------------------------------------------------
void initSubSprites(void){
//-------------------------------------------------------
 
 
 
   oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
 
   int x = 0;
   int y = 0;
   int id = 0;
 
   //set up a 4x3 grid of 64x64 sprites to cover the screen
   for(y = 0; y < 3; y++)
   for(x = 0; x < 4; x++)
   {
      u16 *offset = NULL;
      
      oamSet(&oamSub, id, x * 64, y * 64, 0, 15, SpriteSize_64x64,
            SpriteColorFormat_Bmp, offset, -1, false,false,false,false,false);
      
      oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);         
            
      id++;      
   }
 
   swiWaitForVBlank();
 
   oamUpdate(&oamSub);
}

int initGL ( )
{
	//set mode 0, enable BG0 and set it to 3D
	videoSetMode(MODE_0_3D);
	videoSetModeSub(MODE_5_2D);
	
	// initialize gl
	glInit();
	
 	// sub sprites hold the bottom image when 3D directed to top
	initSubSprites();
 
	// sub background holds the top image when 3D directed to bottom
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	
	//enable textures
	glEnable(GL_TEXTURE_2D);
	
	// enable antialiasing
	glEnable(GL_ANTIALIAS);
	glEnable(GL_BLEND);
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	// setup the rear plane
	glClearColor(1, 1, 1,255); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);

	//this should work the same as the normal gl call
	glViewport(0,0,255,191);
	
	vramSetBankA(VRAM_A_TEXTURE_SLOT0);
	vramSetBankB(VRAM_B_TEXTURE_SLOT1);
	//vramSetBankC(VRAM_C_MAIN_BG_0x06000000);
	//vramSetBankD(VRAM_D_TEXTURE_SLOT2);
	
	/*glGenTextures(1, &textureID);
	glBindTexture(0, textureID);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, (u8*)texture_bin);*/
	
	
	//any floating point gl call is being converted to fixed prior to being implemented
	glMatrixMode(GL_PROJECTION);
	glScalef(1.0f, 1.0f, -1.0f);
	glLoadIdentity();
	glOrtho(-128, 128,-96, 96, 0.1, 100);//gluPerspective(60, 256.0 / 192.0, 0.01, 90); //glOrtho(-3, 3,-2, 2, 0.1, 100);//glOrtho(-128, 128,-96, 96, 0.1, 100);//
	glColor3f(1,1,1);
	gluLookAt(	0.0, 0.0, 1.0,		//camera possition 
				0.0, 0.0, 0.0,		//look at
				0.0, 1.0, 0.0);		//up
	//glTranslatef(-6.8, 4.8, 0);
	//ds uses a table for shinyness..this generates a half-ass one
	//glMaterialShinyness();
	
	glLight(0, RGB15(31,31,31) , 0, floattov10(-1.0), 0);
	
	return 0;
}

int RandomNumber(int min, int max){
	srand(time(0));
	int randNum;
	randNum = -min+(rand()%min);
	return randNum;
}

int	texture[6];		

// Load PCX files And Convert To Textures
int LoadGLTextures() {
	

	int imgSz = 6;
	const unsigned char* img[imgSz];

/*
#include "slot_pcx.h"
#include "Star_pcx.h"
#include "zapah_pcx.h"
#include "twitter_pcx.h"
#include "bg_top_pcx.h"
*/
	img[0] = default_tex_pcx;
	img[1] = bg_top_pcx;
	img[2] = bg_bottom_pcx;
	img[3] = slot_pcx;
	img[4] = zapah_pcx;
	img[5] = inventory_bottom_header_pcx;
	
	/*
	TEXTURE_SIZE_8 = 0,
	TEXTURE_SIZE_16 = 1,
	TEXTURE_SIZE_32 = 2,
	TEXTURE_SIZE_64 = 3,
	TEXTURE_SIZE_128 = 4,
	TEXTURE_SIZE_256 = 5,
	TEXTURE_SIZE_512 = 6,
	TEXTURE_SIZE_1024 = 7 
  */
	int szTex = 5;
	int TextureSize[6];
	/*TextureSize[0] = TEXTURE_SIZE_8;
	TextureSize[1] = TEXTURE_SIZE_16;
	TextureSize[2] = TEXTURE_SIZE_32;
	TextureSize[3] = TEXTURE_SIZE_64;
	TextureSize[4] = TEXTURE_SIZE_128;
	TextureSize[5] = TEXTURE_SIZE_256;
	TextureSize[6] = TEXTURE_SIZE_512;
	TextureSize[7] = TEXTURE_SIZE_1024;*/
	TextureSize[0] = TEXTURE_SIZE_8;
	TextureSize[1] = TEXTURE_SIZE_128;
	TextureSize[2] = TEXTURE_SIZE_128;
	TextureSize[3] = TEXTURE_SIZE_32;
	TextureSize[4] = TEXTURE_SIZE_128;
	TextureSize[5] = TEXTURE_SIZE_8;

	//load our texture
			// (NEW) and different from nehe.
	int i;
	int res = glGenTextures(6, &texture[0]);
	sImage pcx;
	if (res == 1)
	{
		for (i = 0; i < 6; i++)
		{
			
			
				
			int pcxRes = loadPCX((u8*)img[i], &pcx);
			if (pcxRes == 1)
			{
				//cout << "PCX LOADED ***" << endl;
			}
			else
			{
				cout << "PCX NOT LOADED" << endl;
			}
			image8to16(&pcx);

			
			glBindTexture(0, texture[i]);
			int suc = glTexImage2D(0, 0, GL_RGB  , TextureSize[i] , TextureSize[i], 0, TEXGEN_TEXCOORD, pcx.image.data8);
			if (suc == 1)
			{
				//cout << "TEX: " << i << " LOADED SUCCESSFULLY " << endl;
			}
			else
			{
				cout << "FAIL: TEX: " << i << " NOT LOADED " << endl;
			}
			
			imageDestroy(&pcx);
			
		}
	}
	else
	{
			cout << "FUCKKKKKKKKKKKKKKKKKKKKKKK";
	}
	
	
	return TRUE;
}


void drawQuad(int width, int height, int texID)
{
		/*tex = tex + 1;
		if(tex > 5)
			tex = 0;*/

		glBindTexture(GL_TEXTURE_2D, texture[texID]);
		glScalef(width, height, 1);
		glBegin(GL_QUAD);
/*
1, 1    0,1


0,0    1, 0
*/			
			glTexCoord2f(0.0f, 1.0f);//glColor3b(255,0,0);

			glVertex3f(-1, -1, 0);

			glTexCoord2f(1.0f, 1.0f);//glColor3b(0,255,0);

			glVertex3f(1, -1, 0);
			
			
			glTexCoord2f(1.0f, 0.0f);//glColor3b(0,0,255);

			glVertex3f(1, 1, 0);

			glTexCoord2f(0.0f, 0.0f);//glColor3b(255,0,255);

			glVertex3f(-1, 1, 0);
	
		glEnd();

	//glPopMatrix(1);
}



Sprite::Sprite( )
{
	//cout << "SPRITE IS A-OKKK!!!!" << endl;

	
}

void Sprite::setTexture(int _texID)
{
	texID = _texID;
}

void Sprite::newSprite(int _x, int _y, int _width, int _height, int _z, int imgToUse, int texSize)
{
	//LoadGLTextures(imgToUse, texSize);
	//cout << "New Sprite-L! Ok till now "<< endl; 
	//glPushMatrix();
		x = _x;
		y = _y;
		z = _z;
		//glTranslatef32(_x, _y, floattof32(-1));
		width = _width;
		height = _height;
		//size = _size;
		//drawQuad(_width);
	//glPopMatrix(1);
		width = _width;
		glPushMatrix();
			drawQuad(width, height, texID );
		glPopMatrix(1);
		//glTranslatef32(x, y, z);


}

int Sprite::getSize( )
{
	return width, height;
}

int Sprite::getWidth( )
{
	return width;
}

int Sprite::getHeight( )
{
	return height;
}

void Sprite::setSize( int _width, int _height )
{
	//size = _size;
	width = _width;
	height = _height;
}

void Sprite::update( )
{
	glPushMatrix();
		glTranslatef(x, y, z);
		drawQuad(width, height, texID);
	glPopMatrix(1);
}

void Sprite::setX( int _x )
{
	x = _x;
}

int Sprite::getX( )
{
	return x;
}

void Sprite::setY( int _y )
{
	y = _y;
}

int Sprite::getY( )
{
	return y;
}

void Sprite::printSomething( )
{
	//cout << "SOMETHING" << endl;
}
/* 
================= LUA BINDINGS STUFF ===============
*/

int l_initGL(lua_State * l)
{
	initGL( );
	return 0;
}


int l_RandomNumber(lua_State * L)
{
	int x = lua_tonumber(L, 1);
	int y = lua_tonumber(L, 2);
	lua_pushnumber(L, RandomNumber(x, y));
	//lua_pushnumber(L, RandomNumber( lua_tonumber(L,1), lua_tonumber(L,5) ));
	cout << "LOL WORKS" << endl;
	return 1;
	//return 1;
}

/* Sprite Class Constructor */
int l_Sprite_constructor(lua_State * l)
{
 
    Sprite ** udata = (Sprite **)lua_newuserdata(l, sizeof(Sprite *));
    *udata = new Sprite();
 

    luaL_getmetatable(l, "luaL_Sprite");
 

    lua_setmetatable(l, -2);
 

 
    return 1;
}

Sprite * l_CheckSprite(lua_State * l, int n)
{
    // This checks that the argument is a userdata 
    // with the metatable "luaL_Sprite"
    return *(Sprite **)luaL_checkudata(l, n, "luaL_Sprite");
}

/* Sprite::newSprite(int _x, int _y, int _width, int _height, int _z) */
int l_Sprite_newSprite(lua_State * l)
{
	//cout << "Arguments: " << lua_gettop(l)  << endl;
    Sprite * sprite = l_CheckSprite(l, 1);
    /*int a = (int)luaL_checknumber(l, 2);
    int b = (int)luaL_checknumber(l, 3);
 
    std::string s = foo->Add(a, b);
    lua_pushstring(l, s.c_str());*/
	int _x = lua_tointeger(l, 2);
	int _y = lua_tointeger(l, 3);
	int _width = lua_tointeger(l, 4);
	int _height = lua_tointeger(l, 5);
	int _z = lua_tointeger(l, 6);
	int _imgToUse = lua_tointeger(l, 7);
	int _texSize = lua_tointeger(l, 8);
	//cout << "X: " << lua_tointeger(l, 2) << " Y : " << lua_tointeger(l, 3) << " WIDTH: " << lua_tointeger(l, 4) << " HEIGHT: " << lua_tointeger(l, 5) << " Z: " << _z << endl;
	sprite->newSprite(_x, _y, _width, _height, _z, _imgToUse, _texSize);
	
	return 0;
}

int l_Sprite_update(lua_State * l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	sprite->update( );
	return 0;
}

int l_Sprite_printSomething(lua_State * l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	sprite->printSomething( );
	return 0;
}

int l_Sprite_setX(lua_State *l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	sprite->setX( lua_tointeger(l, 2) );
	return 0;
}

int l_Sprite_getX(lua_State *l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	int _x = sprite->getX( );
	//lua_pushinteger( );
	lua_pushnumber(l, lua_tointeger(l,_x) );
	return 1;
}

int l_Sprite_setY(lua_State *l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	sprite->setY( lua_tointeger(l, 2) );
	return 0;
}

int l_Sprite_getY(lua_State *l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	int _y = sprite->getY( );
	//lua_pushinteger( );
	lua_pushnumber(l, lua_tointeger(l,_y) );
	return 1;
}

int l_Sprite_setTexture(lua_State *l)
{
	Sprite * sprite = l_CheckSprite(l, 1);
	sprite->setTexture( lua_tointeger(l, 2) );
}

/*
void Sprite::setX( int _x )
{
	x = _x;
}

int Sprite::getX( )
{
	return x;
}

void Sprite::setY( int _y )
{
	y = _y;
}

int Sprite::getY( )
{
	return y;
}
*/

void RegisterFoo(lua_State * l)
{
    luaL_Reg sFooRegs[] =
    {
        { "new", l_Sprite_constructor },
        { "newSprite", l_Sprite_newSprite },
        { "update", l_Sprite_update },
        { "printSomething", l_Sprite_printSomething },
		{ "setX", l_Sprite_setX },
		{ "getX", l_Sprite_getX },
		{ "setY", l_Sprite_setY },
		{ "getY", l_Sprite_getY },
		{ "setTexture", l_Sprite_setTexture }
    };
 
    // Create a luaL metatable. This metatable is not 
    // exposed to Lua. The "luaL_Foo" label is used by luaL
    // internally to identity things.
    luaL_newmetatable(l, "luaL_Sprite");
 
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
    lua_setglobal(l, "Sprite");
}

