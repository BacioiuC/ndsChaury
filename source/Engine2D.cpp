#include <Engine2D.h>
#include <nds.h>
#include <iostream>
#include <stdio.h>
#include <luascript.h>
//#include "drunkenlogo.h"

// Graphics
#include <bgImages.h>
using namespace std;

static const int DMA_CHANNEL = 3;

Engine2D::Engine2D( )
{

}

void Engine2D::init( )
{
	powerOn(POWER_ALL_2D);

}

void Engine2D::initVideo() {
    /*
     *  Map VRAM to display a background on the main and sub screens.
     * 
     *  The vramSetMainBanks function takes four arguments, one for each of the
     *  major VRAM banks. We can use it as shorthand for assigning values to
     *  each of the VRAM bank's control registers.
     *
     *  We map banks A and B to main screen background memory. This gives us
     *  256KB, which is a healthy amount for 16-bit graphics.
     *
     *  We map bank C to sub screen background memory.
     *
     *  We map bank D to LCD. This setting is generally used for when we aren't
     *  using a particular bank.
     */

					 
					 
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_LCD);

    /*  Set the video mode on the main screen. */
    videoSetMode(MODE_3_2D | // Set the graphics mode to Mode 5
                 DISPLAY_BG2_ACTIVE | // Enable BG2 for display
                 DISPLAY_BG3_ACTIVE); //Enable BG3 for display

    /*  Set the video mode on the sub screen. */
    videoSetModeSub(MODE_5_2D | // Set the graphics mode to Mode 5
                 DISPLAY_BG3_ACTIVE); //Enable BG3 for display
}
/*
 	int  	layer,
		BgType  	type,
		BgSize  	size,
		int  	mapBase,
		int  	tileBase,
		bool  	mainDisplay,
		bool  	loadGraphics 
*/
void Engine2D::initConsoleOutput(int layer, int mapBase, int tileBase, bool mainDisplay )
{
	//consoleDemoInit();
	//consoleInit(0, layer, BgType_Text4bpp, BgSize_B8_256x256, mapBase, tileBase, mainDisplay, true);
	consoleInit(0,layer, BgType_Text4bpp, BgSize_T_256x256, mapBase,tileBase, mainDisplay, true);
	// 2, membase 4
	cout << "Console inited" << endl;

}
/* Initializes a background on either Main or SUbScreen
*  Screen = MAIN | SUB
*  Layer = layer to render it on
*  mapBase = the 2k offset into vram the tile map will be placed
–OR–
the 16k offset into vram the bitmap data will be placed for bitmap backgrounds
*  tileBase	the 16k offset into vram the tile graphics data will be placed 

int  	layer,
		BgType  	type,
		BgSize  	size,
		int  	mapBase,
		int  	tileBase */
//int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
int Engine2D::initBackground256Bmp8(int screen, int layer, int mapBase, int TileBase )
{
	int bg;
	
	if (screen == 1)
	{
		bg = bgInit(layer, BgType_Bmp8, BgSize_B8_256x256, mapBase,TileBase );
	}
	else if (screen == 2)
	{
		bg = bgInitSub(layer, BgType_Bmp8, BgSize_B8_256x256, mapBase, TileBase );
	}
	
	return bg;
}

int Engine2D::initBackground256Text4bpp(int screen, int layer, int mapBase, int TileBase )
{
	int bg;
	
	if (screen == 1)
	{
		bg = bgInit(layer, BgType_Text4bpp, BgSize_T_256x256, mapBase,TileBase );
	}
	else if (screen == 2)
	{
		bg = bgInitSub(layer, BgType_Text4bpp, BgSize_T_256x256, mapBase, TileBase );
	}
	
	return bg;
}

void Engine2D::bgSetPriority(int bg, unsigned int priority)
{
	bgSetPriority(bg, priority);
}

void Engine2D::setupResources( )
{
	//setupGfxArrays( );
}

/*
	Loads the image for the previously created background. Filename should be a extensionless
	name (if loading mainCharacter.bmp, fileName should be mainCharacter
*/
void Engine2D::loadBackgroundImage(int imageID, int bg, int size, bool isSub )
{
	// PAL and BitMap strings
	//imageID = 1;
	//DC_FlushRange(bitMaps[imageID], sizeof(bitMaps[imageID]));
	//DC_FlushRange(palettes[imageID], sizeof(palettes[imageID]));
	
	/*dmaCopy(bitMaps[imageID], bgGetGfxPtr(bg), sizeof(bitMaps[imageID]));
	//DC_FlushRange(palettes[imageID], size*2);
	if (isSub == true)
	{
	
		dmaCopy(palettes[imageID], BG_PALETTE, sizeof(palettes[imageID]));
	}
	else
	{
		dmaCopy(palettes[imageID], BG_PALETTE_SUB, sizeof(palettes[imageID]));
	}
	
	//dmaCopy(drunkenlogoBitmap, bgGetGfxPtr(bg3), 256*256);
	//dmaCopy(drunkenlogoPal, BG_PALETTE, 256*2);
*/

}