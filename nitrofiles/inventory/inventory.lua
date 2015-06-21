inventory = { }

OFFSET_X = - 96
OFFSET_Y = - 128
GRID_SIZE = 32

function inventory:init( )
	self._inventoryTable = { }
	print("WORKS")

	self._inventoryRenderTable = { }
	self._inventoryGrid = { }
	

	self:createHeader( )

end

function inventory:createHeader( )
	self._header = Sprite.new( )
	self._header:newSprite(0, 75, 100, 20, -4, 4, 5)
	self._header:setTexture(INVENTORY_BOTTOM_HEADER_TEX)
	table.insert(self._inventoryRenderTable, self._header)
end

function inventory:createSlots( )
	for x = 1, 6 do
		self._inventoryGrid[x] = { }
		for y = 1, 5 do
			self._inventoryGrid[x][y] = { }
			self._inventoryGrid[x][y].gfx = Sprite.new( )
			self._inventoryGrid[x][y]._x = x*32+OFFSET_X-math.floor(GRID_SIZE/2)
			self._inventoryGrid[x][y]._y = y*32+OFFSET_Y
			self._inventoryGrid[x][y].gfx:newSprite(x*32, y*32, 16, 16, -4, 4, 5)
			self._inventoryGrid[x][y].gfx:setTexture(SLOT_PCX_TEX)
		end
	end

end

function inventory:render( )
	for x = 1, #self._inventoryGrid do
		for y = 1, #self._inventoryGrid[x] do
			local v = self._inventoryGrid[x][y]
			v.gfx:setX(v._x)
			v.gfx:setY(v._y)
			v.gfx:update( )
		end
	end

	for i,v in ipairs(self._inventoryRenderTable) do
		if type(v) == "table" then
			v.gfx:update( )
		else
			v:update( )
		end
	end



end

function inventory:getSlot(_x, _y)
	return self._inventoryGrid[_x][_y]
end