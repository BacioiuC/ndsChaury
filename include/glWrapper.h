#ifndef GLWRAPPER_H
#define GLWRAPPER_H

#include <luascript.h>
#include <nds/arm9/image.h>
#include <lua.hpp>
#include <list>

typedef struct 
{

	int		width;		/*!< Width of the Sprite */      			
	int 	height;		/*!< Height of the Sprite */	
	int 	u_off;		/*!< S texture offset */
	int 	v_off;		/*!< T texture offset */
	int		textureID;  /*!< Texture handle ( used in glDeleteTextures() ) <Br> 
	  						 The texture handle in VRAM (returned by glGenTextures()) <Br>
							 ie. This references the actual texture stored in VRAM */

} glImage;

typedef enum
{

	GL_FLIP_NONE 	= (1 << 0), /*!< No flipping */
	GL_FLIP_V 		= (1 << 1), /*!< Sprite is rendered vertically flipped */
	GL_FLIP_H 		= (1 << 2), /*!< Sprite is rendered horizontally flipped */
	
} GL_FLIP_MODE;

class Sprite {
	public:
		Sprite( );
		~Sprite( );
		int x;
		int y;
		int z;
		int layer; // layer is basically Z :D
		void newSprite(int _x, int _y, int _width, int _height, int _z, int _id);
		void newSpriteBatch(int _x, int _y, int _width, int _height, int _z, int _batchId);
		int width;
		int height;
		int size;
		void update( );
		int depth;
		void setX( int _x );
		int getX( );
		int __getX( );
		void setY( int _y );
		int getY( );
		void setZ( int _z );
		int getZ( );
		int getSize( );
		int getWidth( );
		int getHeight( );
		void setSize( int _width, int _height );
		void printSomething( );
		int texID = 0;
		int id;
		void setTexture(int _texID);
		void setRenderState(bool state);
		bool canRender = true;
		void beginDraw(int x, int y, int z, int _width, int _height);
		void endDraw( );
		void draw();
	private:
		
		void render( );
};
int* returnTextureArray( );
int initGL ( );
int LoadGLTextures();
void SetOrtho( void );
void _glBegin( );
void _glEnd( );
void SetOrtho( );
void _glBegin( );
void _glEnd( );

// LUA Bindings here
int l_initGL(lua_State * L);
int l_RandomNumber(lua_State * L);
Sprite * l_CheckSprite(lua_State * l, int n);
/*int l_Sprite_constructor(lua_State * l);

S
int l_Sprite_newSprite(lua_State * l);
int l_Sprite_update(lua_State * l);*/
void RegisterFoo(lua_State * l);

#endif