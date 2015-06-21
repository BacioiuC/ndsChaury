#ifndef ENGINE2D_H
#define ENGINE2D_H

#include <luascript.h>

class Engine2D {
	public:
	Engine2D( );
	~Engine2D( );
	
	void init( );
	void initVideo();
	void initConsoleOutput(int layer, int mapBase, int tileBase, bool mainDisplay );
	
	// BG Stuff
	int initBackground256Bmp8(int screen, int layer, int mapBase, int TileBase );
	int initBackground256Text4bpp(int screen, int layer, int mapBase, int TileBase );
	void setupResources( );
	void loadBackgroundImage(int imageID, int bg, int size, bool isSub );
	void bgSetPriority(int bg, unsigned int priority);
};

#endif