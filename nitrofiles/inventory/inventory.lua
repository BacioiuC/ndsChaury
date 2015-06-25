inventory = { }



function inventory:init( )
	self._inventoryTable = { }
	print("WORKS")

	self._inventoryRenderTable = { }
	self._inventoryGrid = { }
	

	self:createHeader( )
	self:createSlots( )
end

function inventory:createHeader( )
	self._header = Sprite.new( )
	self._header:newSprite(0, 150, 200, 40, -4, 4, 5)
	self._header:setTexture(INVENTORY_BOTTOM_HEADER_TEX)
	table.insert(self._inventoryRenderTable, self._header)
end

--[[
	Create the top slots!
	Slots on 1st row (Y = 1) are spawners
	Slots created are, by default EMPTY
]]
function inventory:createSlots( )
	for x = 1, 6 do
		self._inventoryGrid[x] = { }
		for y = 1, 5 do
			self._inventoryGrid[x][y] = { }
			self._inventoryGrid[x][y].gfx = Sprite.new( )
			self._inventoryGrid[x][y]._x = x*32
			self._inventoryGrid[x][y]._y = y*32
			self._inventoryGrid[x][y].gfx:newSprite(x*32, y*32, 32, 32, -4, 4, 5)
			self._inventoryGrid[x][y].gfx:setTexture(SLOT_PCX_TEX)
			if y == 1 then
				self._inventoryGrid[x][y].isSpawner = true
			else
				self._inventoryGrid[x][y].isSpawner = false
			end
			self._inventoryGrid[x][y].isEmpty = true
		end
	end
end

function inventory:setEmptyAt(_x, _y)
	self._inventoryGrid[_x][_y].isEmpty = true
end

function inventory:spawnItems( )
	-- only check slots on y = 1
	for x = 1, 6 do
		for y = 1, 5 do
			bool = items:isAt(x, y)
			if bool == true then
				self._inventoryGrid[x][y].isEmpty = false
			else
				self._inventoryGrid[x][y].isEmpty = true
			end
			if self._inventoryGrid[x][1].isEmpty == true then
				self._inventoryGrid[x][1].isEmpty = false
				items:new(x, 1)
				
			end
		end

	end

end

function inventory:isCellEmpty(_x, _y)
	if self._inventoryGrid[_x] ~= nil then
		if self._inventoryGrid[_x][_y] ~= nil then
			return self._inventoryGrid[_x][_y].isEmpty 
		end
	else

	end
	--return true
end

function inventory:render( )
	-- Render the slots
	for x = 1, #self._inventoryGrid do
		for y = 1, #self._inventoryGrid[x] do
			local v = self._inventoryGrid[x][y]
			v.gfx:setX(v._x)
			v.gfx:setY(v._y)
			v.gfx:update( )
		end
	end

	for i,v in ipairs(self._inventoryRenderTable) do
	--	v:update( )
	end


	-- Spawn items
	self:spawnItems( )

end

function inventory:getSlot(_x, _y)
	return self._inventoryGrid[_x][_y]
end