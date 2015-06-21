DEFAULT_TEX = 0
BG_TOP_TEX = 1
BG_BOTTOM_TEX = 2
SLOT_PCX_TEX = 3
ZAPA_PCX_TEX = 4
INVENTORY_BOTTOM_HEADER_TEX = 5
SWORD_PCX_TEX = 6


function awake( )
	--debug.debug ()
	package.path = ""
	dofile("core/renderTable.lua")
	dofile("inventory/inventory.lua")
	dofile("inventory/item.lua")
	renderTable:init( )
	inventory:init( )
	items:init( )
	
end

local i = 0

local mySprite
local topTable = { }
local bottomTable = { }
TouchPressed = false

grid = { }
gridTable = { }


inputMgr = nil

function start( )
	
	--inputMgr = Input.new( )
	--start_new( )
	--initGL( );
	--print(loadlib())

	if package ~= nil then
		--print("FUCK")
		if package.path ~= nil then
			print("WELLL....: ."..package.path.."")
		else
			print("Thank you o/")
		end
	end

	--inventory:init( )
	local temp = {
		sprite = Sprite.new( ),
		priority = 0,
	}
	temp.sprite:newSprite(0, 0, 140, 100, -5, 4, 5)
	temp.sprite:setTexture(BG_TOP_TEX)
	--renderTable:add(temp.sprite, 1, 1, 1)
	table.insert(topTable, temp)

	local temp = {
	sprite = Sprite.new( ),
	priority = 0,
	}
	temp.sprite:newSprite(0, 0, 140, 100, -5, 4, 5)
	temp.sprite:setTexture(BG_BOTTOM_TEX)
	table.insert(bottomTable, temp)	
	--renderTable:add(temp.sprite, 1, 1, 2)

	inventory:createSlots( )

	inputMgr = Input.new( ) -- get our Input started
	
	items:new( )
	
end


function createGridOfSlots( )

end

function handleInput(_px, _py)
	--print("PX: ".._px.." PY: ".._py.."")
	local v = items:getItem(1)
	if v ~= nil then
		if TouchPressed == true then
			v:setX( math.floor(tonumber(_px))- 96)
			v:setY(-math.floor(tonumber(_py)-92))
		end
	end
end

function renderTop( )
	--print("LOOPING")
	--SpriteClass:update( )
	for i,v in ipairs(topTable) do

		v.sprite:update( )
	end
	--renderTable:render(1)

	--mySlot:update( )
end


function renderBottom( )
	
	for i,v in ipairs(bottomTable) do
		--v.sprite:setX(math.random(0, 255));
		--v.sprite:setY(-math.random(0, 50));
		--print("Y IS: "..v.sprite:getY( ));
		v.sprite:update( )
	end
	
	--renderTable:render(2)
	inventory:render( )
	items:update( )
	inputMgr:touchLoop()

	TouchPressed = inputMgr:getTouchState( )


	handleInput(inputMgr:getX( ), inputMgr:getY( ))

	
	
	--print("PX IS: "..px.." | PY: "..py.."")

	--print("PX IS : "..px.. " PY IS: "..py.."")
end



function renderTable(_table)
	
end



