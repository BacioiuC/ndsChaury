ndsChaury:
================================
ndsChaury is my attempt at using devkitarm, C++, lua and libdns's openGL-like calls to create a 2D game engine for the Nintendo DS. The end goal is to use it in order to design and prototype 2D games that I can take with me and show off on the Nintendo DS. **NOTE:** This is in no way a  project aimed towards production use. Keep in mind that I am a really bad programmer and my code should not be used as an example. Use it at your own risk.

<dl>
<dt>Rendering: 3D using an openGL-ish interface provided by libnds</dt>
</dl>

<pre>
GLWrapper.h/.cpp contains functions for rendering a QUAD and loading/applying textures. It also contains a Sprite class 
that uses drawQuad to draw it's elements. For now, it only does the basics:
* Create a new sprite
* Apply a texture
* Set it's X/Y position
* Get the sprite's X/Y position
* Destroy said sprite
* All functions are exposed to lua. 
Example loading and rendering a sprite in Lua:
local mySprite = Sprite:new( )
mySprite:newSprite(0, 0, 140, 100, -1, 4, 5) -- x, y, width, height, DEPTH. Last two parameters are not used for now
mySprite::setTexture(BG_TOP_TEX) -- images and textures are loaded and included during the build process. You just
-- need to pas the index at which the texture is positioned in the texture array
renderTable:adt(mySprite, 1, 1, 1) -- Sprite, The layer on which to render, Rendering Priority, On what screen to Render (Top/Bottom)
</pre>

<dl>
<dt>Rendering 3D Quads on both screens: </dt>
</dl>
<pre>
This is handled in the main loop in main.cpp and exposed to lua via the renderTop( ) and renderBottom( ) function. Place
your sprite update functions in one of the two functions to render them each frame (alternatively, adt them to the
renderTable and it will handle rendering them itself).

Rendering on both screen is done by swapping the main screen position every frame and keeping the previous frame in
memory in a buffer (see main.cpp While(true) ). For an easier example (less code to navigate through) check out the 
3D_Both_Screens example that comes with devkitpro.
</pre>

<dl>
<dt>Lua: binding done without the use of Luabind/tolua++, etc </dt>
</dl>

<pre>
I decided to embedt lua without any helpful libraries (like LuaBind) so I can learn how to do it properly. This is a learning 
/ study project after all :). There are 4 Lua functions that the host listens for: awake( ), start( ), renderTop( ), 
renderBottom( ). Use awake to initialize your stuff and include other lua files (for some reason require doesn't quite work
as intended, dofile("x/y.lua") does a good job for now.
</pre>

<dl>
<dt>Images get loaded and adted during the build process </dt>
</dl>
<pre>
For now, all images need to be saved as .pcx's inside the /data folder. In glWrapper.cpp you must include a header 
named after the image in order to be able to use the image. Example: my_image.pcx must be included as
#include "my_image_pcx.h". This will change in the future, but gotta finish the basics first.
</pre>

<dl>
<dt>Input - touch inputs </dt>
</dl>
<pre>
To listen and use inputs you must create a Input manager object, using myInput = Input:new( ) and then, somewhere in
the update functions, listen for input via myInput:touchLoop( ). You can acess the X and Y input points via myInput:getX( )
and myInput:getY( ).
</pre>

![](/docs/input_almost.gif)


License
====================
The MIT License (MIT)

Copyright (c) 2015 Bacioiu Ciprian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.



