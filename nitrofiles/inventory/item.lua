
items = { }

function items:init( )
	self._itemTable = { }
	--self:new( )

	--items:new(32, 16)

end

function items:new(_x, _y)
	local temp = { 
		--id = #self._itemTable + 1,
		gfx = Sprite:new( ),
		x = _x,
		y = _y,
		ofx = 0,
		ofy = 0,
		inity = _y,
		gravityTimer = 0,
		maxFallTime = 3,
		hp = 10,
	}
	temp.gfx:newSprite(_x, _y, 32, 32, -1, 4, 5)
	temp.gfx:setTexture(SWORD_PCX_TEX)
	table.insert(self._itemTable, temp)

	return temp.id
end

function items:isAt(_x, _y)
	for i,v in ipairs(self._itemTable) do
		if v ~= nil and v.hp > 0 then
			if v.x == _x and v.y == _y then
				return true
			end
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

function items:getItemAt(_x, _y)
	for i,v in ipairs(self._itemTable) do
		if v ~= nil then
			if v.x == _x and v.y == _y then
				return i
			end
		end
	end
end

function items:destroy(_id)
	local v = self._itemTable[_id]
	if v~=nil then
		v.y = 1000
		v.x = 1000
		--v.gfx:setRenderState(false)
		inventory:setEmptyAt(v.x, v.y)
		v.gfx = nil
		v = nil
		table.remove(self._itemTable, i)
		--self:updateIndex( )
	end

end

function items:updateIndex( )
	for i,v in ipairs(self._itemTable) do
		--v.id = i
	end
end

function items:update( )



	for i,v in ipairs(self._itemTable) do
		if v ~= nil then
			-- make differance between initial y and current y
			if v.gfx ~= nil and v.hp > 0 then
				if self:isAt(v.x, v.y+1) == false then
					if v.y < 5 then

							--v.y = v.y + 1
							--if v.ofy < 32 then
							--	v.ofy = v.ofy + 1
							--end
							
							--if v.ofy == 32 then
							v.y = v.y + 1
							--	v.ofy = 0
							--end


					end
				end
				
				v.gfx:setX(v.x*32)
				v.gfx:setY(v.y*32)
				v.gfx:update( )
			end

			if v.hp == 0 then
				self:destroy(i)
			end
		end

	end


end

function items:handleInput(_px, _py)
	if TouchPressed == true then
		local x = math.floor(_px/32)
		local y = math.floor(_py/32)
		local v = self._itemTable[self:getItemAt(x, y)]
		print("X: "..x.." Y: "..y.."")
		if v ~= nil then
			v.hp = 0
		end
	end
end