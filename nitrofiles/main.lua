DEFAULT_TEX = 0
BG_TOP_TEX = 1
BG_BOTTOM_TEX = 2
SLOT_PCX_TEX = 3
ZAPA_PCX_TEX = 4
INVENTORY_BOTTOM_HEADER_TEX = 5
ZAPA_PCX_TEX = 6

function awake( )
	--debug.debug ()
	package.path = ""
	dofile("core/renderTable.lua")
	dofile("inventory/inventory.lua")
	renderTable:init( )
	inventory:init( )
	
end

local i = 0

local mySprite
local topTable = { }
local bottomTable = { }


grid = { }
gridTable = { }


inputMgr = nil

function start( )
	
	--inputMgr = Input.new( )
	--start_new( )
	--initGL( );
	--print(loadlib())

	if package ~= nil then
		print("FUCK")
		if package.path ~= nil then
			print("WELLL....: ."..package.path.."")
		else
			print("FUCKITY FUCK FUCK")
		end
	end

	--inventory:init( )
	local temp = {
		sprite = Sprite.new( ),
		priority = 0,
	}
	temp.sprite:newSprite(0, 0, 140, 100, -1, 4, 5)
	temp.sprite:setTexture(BG_TOP_TEX)
	renderTable:add(temp.sprite, 1, 1, 1)
	--table.insert(topTable, temp)

	local temp = {
	sprite = Sprite.new( ),
	priority = 0,
	}
	temp.sprite:newSprite(0, 0, 140, 100, -1, 4, 5)
	temp.sprite:setTexture(BG_BOTTOM_TEX)
	--table.insert(bottomTable, temp)	
	renderTable:add(temp.sprite, 1, 1, 2)

	inventory:createSlots( )

	inputMgr = Input.new( ) -- get our Input started
	

	
end


--[[
		local sortedEvaTable = { }
		if evaluationTable ~= nil then
			for i,v in spairs(evaluationTable, function(t,a,b) return t[b].value < t[a].value end) do
				table.insert(sortedEvaTable, v)
			end		

			-- first item in the table should be the most INTERESTING ONE! Return it
			if #sortedEvaTable ~= nil then
				return sortedEvaTable[1]
			end
		end
]]


function createGridOfSlots( )
	--[[for i = 
	for x = 1, 6 do
		for y = 1, 4 do
			local temp = {
				sprite = Sprite.new( ),
				priority = 1,
			}
			temp.sprite:newSprite(x * 2 - x +OFFSET_X, y, 1, 1, -1, 4, 5)
			temp.sprite:setTexture(SLOT_PCX_TEX)
			table.insert(bottomTable, temp)
		end
	end
	for x = 1, 3 do
		grid[x] = { }
		for y = 1, 2 do
			grid[x][y] = 1
		end
	end--]]





end

function handleInput(_px, _py)
	--print("PX: ".._px.." PY: ".._py.."")
	local v = inventory:getSlot(3, 3)
	v._x = math.floor(tonumber(_px))- 96
	v._y = -math.floor(tonumber(_py)-92)
end

function renderTop( )
	--print("LOOPING")
	--SpriteClass:update( )
	for i,v in ipairs(topTable) do

		v.sprite:update( )
	end
	renderTable:render(1)

	--mySlot:update( )
end


function renderBottom( )

	for i,v in ipairs(bottomTable) do
		--v.sprite:setX(math.random(0, 255));
		--v.sprite:setY(-math.random(0, 50));
		--print("Y IS: "..v.sprite:getY( ));
		v.sprite:update( )
	end

	inventory:render( )

	inputMgr:touchLoop()
	handleInput(inputMgr:getX( ), inputMgr:getY( ))

	renderTable:render(2)
	--print("PX IS: "..px.." | PY: "..py.."")

	--print("PX IS : "..px.. " PY IS: "..py.."")
end



function renderTable(_table)
	
end



