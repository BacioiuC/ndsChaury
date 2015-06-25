#include <spriteBatch.h>
#include <nds.h>
#include <luascript.h>
#include <lua.hpp>
#include <glWrapper.h>


spriteBatch::spriteBatch( )
{
	//batchList = new list<Sprite>;
 
} 

bool spriteBatch::add(Sprite* mySprite, int _x, int _y, int _width, int _height, int _z)
{
	spriteData newSprite;
	newSprite.sprite = mySprite;
	newSprite.x = _x;
	newSprite.y = _y;
	newSprite.z = _z;
	newSprite.width = _width;
	newSprite.height = _height;
	
	batchList.insert(batchList.end(), newSprite);
  
	x = _x;
	y = _y;
	z = _z;
	width = _width;
	height = _height;

}  
  
void spriteBatch::update(Sprite* mySprite, int _x, int _y, int _z)
{
	spriteData newSprite;
	newSprite.sprite = mySprite;
	newSprite.x = _x;
	newSprite.y = _y;

    for(list<spriteData>::iterator it=batchList.begin();it!=batchList.end();++it)
    {
		
		if( (*it).sprite == newSprite.sprite)
		{
			(*it).x = newSprite.x;
			(*it).y = newSprite.y;
		} 
	}	 
}     
 
void spriteBatch::render( )
{    
	
	//
	int* texArray = returnTextureArray( );
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texArray[4]);
	//glScalef(width, height, 1);
	glBegin(GL_QUAD);
    for(list<spriteData>::iterator it=batchList.begin();it!=batchList.end();++it)
    {
		glPushMatrix();

		glTranslatef( (*it).x, -(*it).y, -4);
		glScalef((*it).width, -(*it).height, 1);

		(*it).sprite->draw();
		
		glScalef(0, 0, 0);
		glTranslatef(0, 0, 0);
		glPopMatrix(1);
		
      
    }  
	glEnd();
	
	glBindTexture(0,0);
	glPopMatrix(1);
	
}

/* Sprite Class Constructor */
int l_spriteBatch_constructor(lua_State * l)
{
 
    spriteBatch ** udata = (spriteBatch **)lua_newuserdata(l, sizeof(spriteBatch *));
    *udata = new spriteBatch();
 

    luaL_getmetatable(l, "luaL_spriteBatch");
 

    lua_setmetatable(l, -2);
 

 
    return 1;
}

spriteBatch * l_CheckspriteBatch(lua_State * l, int n)
{
    // This checks that the argument is a userdata 

    return *(spriteBatch **)luaL_checkudata(l, n, "luaL_spriteBatch");
}

int l_spriteBatch_add(lua_State * l)
{
	spriteBatch * myBatch = l_CheckspriteBatch(l, 1);
	Sprite* mySprite = (Sprite*)lua_touserdata(l, 2);
	// int _x, int _y, int _width, int _height, int _z
	int _x = lua_tointeger(l, 3);
	int _y = lua_tointeger(l, 4);
	int _width = lua_tointeger(l, 5);
	int _height = lua_tointeger(l, 6);
	int _z = lua_tointeger(l, 7);
	
	myBatch->add(mySprite, _x, _y, _width, _height, _z);
	return 0;
}  
 
int l_spriteBatch_update(lua_State *l)
{
	spriteBatch * myBatch = l_CheckspriteBatch(l, 1);
	Sprite* mySprite = (Sprite*)lua_touserdata(l, 2);
	int _x = lua_tointeger(l, 3);
	int _y = lua_tointeger(l, 4);
	int _z = lua_tointeger(l, 7);
	myBatch->update(mySprite, _x, _y, _z);
 
} 

int l_spriteBatch_render(lua_State *l)
{
	spriteBatch * myBatch = l_CheckspriteBatch(l, 1);
	myBatch->render( );
	return 0;
} 

void RegisterSpriteBatch(lua_State * l)
{
    luaL_Reg sFooRegs[] =
    {
        { "new", l_spriteBatch_constructor },
        { "add", l_spriteBatch_add },
		{ "render", l_spriteBatch_render },
		{ "update", l_spriteBatch_update }
 
    };
 
    // Create a luaL metatable. This metatable is not 
    // exposed to Lua. The "luaL_Foo" label is used by luaL
    // internally to identity things.
    luaL_newmetatable(l, "luaL_spriteBatch");
  
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
    lua_setglobal(l, "spriteBatch");
}