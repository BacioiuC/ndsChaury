DEFAULT_TEX = 0
BG_TOP_TEX = 1
BG_BOTTOM_TEX = 2
SLOT_PCX_TEX = 3
ZAPA_PCX_TEX = 4
INVENTORY_BOTTOM_HEADER_TEX = 5
SWORD_PCX_TEX = 6

OFFSET_X = 128
OFFSET_Y = - 96
GRID_SIZE = 32

function awake( )
	--debug.debug ()
	package.path = ""
	--dofile("core/renderTable.lua")
	--dofile("inventory/inventory.lua")
	--dofile("inventory/item.lua")

	
end

local i = 0

local mySprite
local topTable = { }
local bottomTable = { }
local myTable = { }
TouchPressed = false

grid = { }
gridTable = { }

nrSprites = 0

inputMgr = nil
local myBatch 
local myBatch2
local timer = 0
function start( )
	

	local temp = {
		sprite = Sprite.new( ),
		priority = 0,
	}
	temp.sprite:newSprite(0,  0, 256, 192, -15, 4, 5)
	temp.sprite:setTexture(BG_TOP_TEX)
	--renderTable:add(temp.sprite, 1, 1, 1)
	table.insert(topTable, temp)

	local temp = {
	sprite = Sprite.new( ),
	priority = 0,
	}
	temp.sprite:newSprite(0, 0, 256, 192, -15, 4, 5)
	temp.sprite:setTexture(BG_BOTTOM_TEX)
	table.insert(bottomTable, temp)	


	

	inputMgr = Input.new( ) -- get our Input started
	
	myBatch = spriteBatch.new( )
	myBatch2 = spriteBatch.new( )
	newSprite( )
	
end

function newSprite( )
	local x = math.random(1, 8)
	local y = math.random(1, 6)
	local temp = {
		sprite = Sprite.new( ),
		on = true,
		_x = x,
		_y = y,
		timeStep = 0,
		startTimer = 0,
	}
	temp.sprite:newSprite(x*32-32, y*32-32, 32, 32, -4, 4, 5)
	temp.sprite:setX(x*32-32)
	temp.sprite:setY(y*32-32)
	temp.sprite:setTexture(ZAPA_PCX_TEX)
	--table.insert(myTable, temp)
	nrSprites = nrSprites + 1
	local a = math.random(1, 2)
	if a == 1 then
		myBatch:add(temp.sprite, x*32-32, y*32-32, 32, 32, -4)
	else
		myBatch2:add(temp.sprite, x*32-32, y*32-32, 32, 32, -4)
	end

end


function createGridOfSlots( )

end

function handleInput(_px, _py)
	--items:handleInput(_px, _py)
	if TouchPressed == true then
		newSprite( )
	end
end

function renderTop( )

	--print("LOOPING")
	--SpriteClass:update( )
	for i,v in ipairs(topTable) do
		v.sprite:update( )
	end
	--renderTable:render(1)
	print("NR Sprites: "..nrSprites.."  ")
	if nrSprites < 1000 then
		newSprite( )
	end


	myBatch:render( )
	--mySlot:update( )
end


function renderBottom( )
	
	for i,v in ipairs(bottomTable) do

		v.sprite:update( )
	end
	

	inputMgr:touchLoop()

	TouchPressed = inputMgr:getTouchState( )


	handleInput(inputMgr:getX( ), inputMgr:getY( ))
	myBatch2:render( )
	

end



function renderTable(_table)
	
end



