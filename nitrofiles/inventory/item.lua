
items = { }

function items:init( )
	self._itemTable = { }
	--self:new( )
end

function items:new( )
	local temp = { 
		id = #self._itemTable + 1,
		gfx = Sprite:new( ),

	}
	temp.gfx:newSprite(-80, -64, 32, 32, -1, 4, 5)
	temp.gfx:setTexture(SWORD_PCX_TEX)
	table.insert(self._itemTable, temp)

	return temp.id
end

function items:getItem(_id)
	local v = self._itemTable[_id].gfx
	return v
end

function items:update( )
	for i,v in ipairs(self._itemTable) do
		--v.gfx:setX(-80)
		--v.gfx:setY(64)
		v.gfx:update( )
	end
end