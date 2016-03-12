/*---------------------------------------------------------------------------------

	LUA NDS something something game engine
	Uses: LibNDS, NITROFS and the wonderful devkitarm tool-chain
	LUASCRIPT based on EliasD tutorial: https://github.com/EliasD/unnamed_lua_binder

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <nds/arm9/image.h>
#include <iostream>
#include <stdio.h>
#include <lua.hpp>
#include "lauxlib.h"
#include <filesystem.h>
#include <dirent.h>
#include <fstream>
#include <luascript.h>
#include <Engine2D.h>

// GL Wrapper
#include <glWrapper.h>
#include <spriteBatch.h>
#include <input.h>

// Engine stuff




volatile int frame = 0;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}

using namespace std;


int setLuaPath( lua_State* L, const char* path )
{
    lua_getglobal( L, "package" );
    lua_getfield( L, -1, "path" ); // get field "path" from table at top of stack (-1)
    std::string cur_path = lua_tostring( L, -1 ); // grab path string from top of stack
    cur_path.append( ";" ); // do your path magic here
    cur_path.append( path );
    lua_pop( L, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring( L, cur_path.c_str() ); // push the new one
    lua_setfield( L, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( L, 1 ); // get rid of package table from top of stack
    return 0; // all done!
}

//---------------------------------------------------------------------------------
void dirlist(const char* path) {
//---------------------------------------------------------------------------------

	DIR* pdir = opendir(path);

	if (pdir != NULL) {

		while(true) {
			struct dirent* pent = readdir(pdir);
			if(pent == NULL) break;
			
			if(strcmp(".", pent->d_name) != 0 && strcmp("..", pent->d_name) != 0) {
				if(pent->d_type == DT_DIR) {
					printf("%s/%s <DIR>\n", (strcmp("/",path) == 0)?"":path, pent->d_name);
					char *dnbuf = (char *)malloc(strlen(pent->d_name)+strlen(path)+2);
					sprintf(dnbuf, "%s/%s", (strcmp("/",path) == 0)?"":path, pent->d_name);
					dirlist(dnbuf);
					free(dnbuf);
				} else {
					printf("%s/%s\n",(strcmp("/",path) == 0)?"":path, pent->d_name);
				}
			}
		}
		
		closedir(pdir);
	} else {
		printf("opendir() failure.\n");
	}
}

//---------------------------------------------------------------------------------

void setupLuaFunction(LuaScript s)
{
	//s.;
}

//-------------------------------------------------------
void renderScene(LuaScript script, bool top){
//-------------------------------------------------------
	static short angle = 0;
 
	/*if(top)
		renderCube(angle);
	else
		renderPyramid(angle);*/
	if(top)
	{
		script.getGlobal("renderTop");
		if(script.isFunction( ))
		{
			script.call( );
			
		}		
	}
	else
	{
		script.getGlobal("renderBottom");
		if(script.isFunction( ))
		{
			script.call( );
			
		}		
	}
	angle++;
}
	//consoleDemoInit();
	//consoleInit(0,1, BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true); 
	
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	touchPosition touch;

	//irqSet(IRQ_VBLANK, Vblank);
	initGL ( );
	
	
	vramSetBankF(VRAM_F_MAIN_BG);
	//consoleInit(0, 1, BgType_Text4bpp, BgSize_T_256x256, 7,0, true, true);
	consoleInit(0,1, BgType_Text4bpp, BgSize_T_256x256, 7,0, true, true);
	//consoleDebugInit(DebugDevice_CONSOLE);
	LoadGLTextures();
	
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK  | POLY_FORMAT_LIGHT0);
	/*
	Init NitroFS
	*/
	nitroFSInit(NULL);

	//Write some test files
	

   FILE *fp;

   fp = fopen("test.txt", "w+");
   fprintf(fp, "This is testing for fprintf...\n");
   fputs("This is testing for fputs...\n", fp);
   fclose(fp);;


	//dirlist("/");
	/*
	LUA GOES HERE TEST
	*/
	bgSetPriority(0,0);
	bgSetPriority(1,0);
	cout << "TEST INIT; " << endl;
    LuaScript script("main.lua");
    script.loadFile("main.lua");

    if(script.GetExecutionStatus() == true)
    {
	    //setLuaPath(script.getLuaState(), "/");
		//script.loadFile("test1.lua");
		script.pushFunction((lua_CFunction)l_initGL, "initGL");
		script.pushFunction((lua_CFunction)l_RandomNumber, "RandomNumber");


		
		RegisterFoo(script.getLuaState( ));
		RegisterInput(script.getLuaState( ));
		RegisterSpriteBatch(script.getLuaState( ));

		script.getGlobal("awake"); // get the start method and handle anything related to displaying stuff and etc
		if(script.isFunction( ))
		{
			script.call( );
		}
		
		script.getGlobal("start"); // get the start method and handle anything related to displaying stuff and etc
		if(script.isFunction( ))
		{
			script.call( );
		}	
    }
    else
    {

    	cout << "Error in executing the script! GetExecutionStatus == false" << endl;
    }



	/* END OF LUA */


	bool top = true;

	int keys;

	
	while(true) {
	
		
		scanKeys();
		touchRead(&touch);
		int pressed = keysDown();	
		int held = keysHeld();		
		_glBegin( );
		top = !top;
		if(top)
		{

			lcdMainOnBottom();
			vramSetBankC(VRAM_C_LCD);
			vramSetBankD(VRAM_D_SUB_SPRITE);
			REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
		}
		else
		{

			lcdMainOnTop();
			vramSetBankD(VRAM_D_LCD);
			vramSetBankC(VRAM_C_SUB_BG);
			REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
		}
	 
		glMatrixMode(GL_MODELVIEW);

		if(script.GetExecutionStatus() == true)
   		{
			if(top) 
			{
				bgSetPriority(0,1);
				bgSetPriority(1,0);	
				script.getGlobal("renderTop");
				if(script.isFunction( ))
				{
					script.call( );
					
				}	
			}
			else
			{
				bgSetPriority(0,0);
				bgSetPriority(1,0);
				script.getGlobal("renderBottom");
				if(script.isFunction( ))
				{
					script.call( );
				
				}		
			}
		}
		else
		{
			if(top) 
			{
				bgSetPriority(0,1);
				bgSetPriority(1,0);	
	
			}
			else
			{
				bgSetPriority(0,0);
				bgSetPriority(1,0);
	
			}
			//cout << "Error " << endl;
		}

		_glEnd( );
		glFlush(0);
		
		swiWaitForVBlank();
		
		
		keys = keysDown();	
		
	}

	return 0;
}
