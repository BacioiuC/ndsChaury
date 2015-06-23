
items = { }

function items:init( )
	self._itemTable = { }
	--self:new( )

	items:new(32, 16)

end

function items:new(_x, _y)
	local temp = { 
		id = #self._itemTable + 1,
		gfx = Sprite:new( ),
		x = _x,
		y = _y,
		ofx = 0,
		ofy = 0,
		inity = _y,
		gravityTimer = 0,
		maxFallTime = 0.1,
	}
	temp.gfx:newSprite(_x, _y, 32, 32, -1, 4, 5)
	temp.gfx:setTexture(SWORD_PCX_TEX)
	table.insert(self._itemTable, temp)

	return temp.id
end

function items:isAt(_x, _y)
	for i,v in ipairs(self._itemTable) do
		local dif = v.inity - v.y
	 	local modulo = 0

		if v.x == _x and 1+dif+modulo == _y then
			return true
		end
	end
	return false
end

function items:generateItems(_x, _y)
	-- generate the first row of items

end


function items:getItem(_id)
	local v = self._itemTable[_id].gfx
	return v
end
--[[
*32+OFFSET_X-math.floor(GRID_SIZE/2)
*32+OFFSET_Y
]]
function items:update( )
	--[[for i,v in ipairs(self._itemTable) do
		-- make differance between initial y and current y
		local dif = v.inity - v.y
		if inventory:isCellEmpty(v.x, 1+dif+2) == true then
			if v.y > -3 then
				v.gravityTimer = v.gravityTimer + 1
				if v.gravityTimer > v.maxFallTime then
					if v.ofy < 32 then
						v.ofy = v.ofy + 1
					end

					if v.ofy == 32 then
						v.y = v.y - 1
						v.ofy = 0
					end
					v.gravityTimer = 0
				end
			end
		end
		v.gfx:setX(v.x*32+OFFSET_X-math.floor(GRID_SIZE/2))
		v.gfx:setY(v.y*32+8-v.ofy)
		v.gfx:update( )
	end--]]
	for i,v in ipairs(self._itemTable) do
		v.gfx:update( )
	end
end